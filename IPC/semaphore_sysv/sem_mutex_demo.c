#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define KEY_PATH "./semtest"
#define KEY_ID 1
#define WRITE_FILE "./a.txt"
#define LOOP_COUNT 3

int sem_grp_id = -1;

int create_sem_group(int semnum)
{
    FILE * key_file = fopen(KEY_PATH,"a+");
    if(key_file == NULL)
    {
        perror("fopen");
        return -1;
    }
    fclose(key_file);

    key_t key = ftok(KEY_PATH,KEY_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }

    int sem_group_id = semget(key,semnum,0664 | IPC_CREAT);
    if(sem_group_id < 0)
    {
        perror("semget");
        return -1;
    }
    return sem_group_id;
}

int set_sem_val(int sem_group_id,int semindex,int val)
{
    int ret = semctl(sem_group_id,semindex,SETVAL,val);
    if(ret < 0)
    {
        perror("semctl SETVAL");
        return -1;
    }
    return 0;
}

int rm_sem_group(int sem_group_id)
{
    if(semctl(sem_group_id,0,IPC_RMID) < 0)
    {
        if(errno == EINVAL || errno == EIDRM)
        {
            return 0;
        }
        perror("semctl IPC_RMID");
        return -1;
    }
    printf("delete sem group\n");
    return 0;
}

int sem_p(int sem_group_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    int ret = semop(sem_group_id,&sem_buf,1);
    if(ret < 0)
    {
        perror("semop P");
        return -1;
    }
    return 0;
}

int sem_v(int sem_group_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;
    int ret = semop(sem_group_id,&sem_buf,1);
    if(ret < 0)
    {
        perror("semop V");
        return -1;
    }
    return 0;
}

void my_ext(int sig)
{
    (void)sig;
    if(sem_grp_id >= 0)
    {
        rm_sem_group(sem_grp_id);
    }
    _exit(EXIT_SUCCESS);
}

void write_data(const char * left,const char * right)
{
    FILE * file = fopen(WRITE_FILE,"a+");
    if(file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fwrite(left,1,strlen(left),file);
    fwrite(right,1,strlen(right),file);
    fwrite("\n",1,1,file);
    fflush(file);
    fclose(file);
}

void run_worker(const char * name,const char * left,const char * right)
{
    int i;
    for(i = 0;i < LOOP_COUNT;i++)
    {
        if(sem_p(sem_grp_id) < 0)
        {
            exit(EXIT_FAILURE);
        }
        printf("%s process get sem success\n",name);
        write_data(left,right);
        sleep(1);
        if(sem_v(sem_grp_id) < 0)
        {
            exit(EXIT_FAILURE);
        }
        printf("%s process release sem success\n",name);
    }
}

int main()
{
    if(signal(SIGINT,my_ext) == SIG_ERR)
    {
        perror("signal");
        return -1;
    }

    sem_grp_id = create_sem_group(1);
    if(sem_grp_id < 0)
    {
        return -1;
    }

    if(set_sem_val(sem_grp_id,0,1) < 0)
    {
        rm_sem_group(sem_grp_id);
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        rm_sem_group(sem_grp_id);
        return -1;
    }
    else if(pid == 0)
    {
        run_worker("child","12343","213456");
        _exit(EXIT_SUCCESS);
    }

    run_worker("parent","hello","world");

    if(waitpid(pid,NULL,0) < 0)
    {
        perror("waitpid");
        rm_sem_group(sem_grp_id);
        return -1;
    }

    if(rm_sem_group(sem_grp_id) < 0)
    {
        return -1;
    }
    return 0;
}
