#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
/* Code by GUDDU SHARMA */
struct PCB
{
    int process_no, id;
    int cpu_burstTime, io_burstTime, total_burstTime, arrival_Time;
    int turnaround_Time, wait_Time, response_Time, completion_Time;
    int priority;
    char *status; //WHETHER I/O BOUND OR CPU BOUND PROCESS
    struct PCB *next;
};
/* Code by GUDDU SHARMA */
struct Queue
{
    struct PCB *front, *rear;
};
/* Code by GUDDU SHARMA */
struct PCB *newNode(int pno, int id, int cpb, int iob, int tb, int at, char sta[], int p)
{
    struct PCB *temp = (struct PCB *)malloc(sizeof(struct PCB));
    temp->process_no = pno;
    temp->id = id;
    temp->cpu_burstTime = cpb;
    temp->io_burstTime = iob;
    temp->total_burstTime = tb;
    temp->arrival_Time = at;
    temp->status = sta;
    temp->priority = p;
    temp->next = NULL;
    return temp;
};
/* Code by GUDDU SHARMA */
struct Queue *createProcess()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
/* Code by GUDDU SHARMA */
void enQueue(struct Queue *q, int pno, int id, int cpb, int iob, int tb, int at, char sta[], int p)
{
    struct PCB *temp = newNode(pno, id, cpb, iob, tb, at, sta, p);
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}
/* Code by GUDDU SHARMA */
void Print_PCB(struct Queue *q)
{
    struct PCB *temp = q->front;
    if((temp == NULL) && (q->rear == NULL))
        printf("\n\nQUEUE IS EMPTY\n");
    else
    {
        while(temp != NULL)
        {
            printf("%5d \t %12d \t %5d \t %7d \t %5d \t %6d     %s", temp->process_no, temp->id, temp->cpu_burstTime, temp->io_burstTime, temp->total_burstTime, temp->arrival_Time, temp->status);
            temp = temp->next;
            printf("\n");
        }
    }
}
void Print_table_FCFS(struct Queue *q)
{
    struct PCB *temp = q->front;
    if((temp == NULL) && (q->rear == NULL))
        printf("\n\nQUEUE IS EMPTY\n");
    else
    {
        while(temp)
        {
            printf("%5d \t %8d \t %3d \t %4d  %6d  %5d ", temp->process_no, temp->total_burstTime, temp->arrival_Time, temp->turnaround_Time, temp->wait_Time, temp->response_Time);
            temp = temp->next;
            printf("\n");
        }
    }
}
/* Code by GUDDU SHARMA */
void Print_table_SJF(struct Queue *q)
{
    struct PCB *temp = q->front;
    if((temp == NULL) && (q->rear == NULL))
        printf("\n\nQUEUE IS EMPTY\n");
    else
    {
        while(temp)
        {
            printf("%5d \t %8d \t %3d \t %4d \t %6d  %6d  %5d ", temp->process_no, temp->total_burstTime, temp->arrival_Time, temp->priority, temp->turnaround_Time, temp->wait_Time, temp->response_Time);
            temp = temp->next;
            printf("\n");
        }
    }
}
/* Code by GUDDU SHARMA */
void cal_TAT_WT_RT_FCFS(struct Queue *q, int n)
{
    struct PCB *temp = q->front;
    int i, time = 0;
    for(i=1; i<=n; i++)
    {
        time = time + temp->total_burstTime;
        temp->turnaround_Time = time - (temp->arrival_Time);
        temp->wait_Time = (temp->turnaround_Time) - (temp->total_burstTime);
        temp->response_Time = (temp->turnaround_Time) - (temp->total_burstTime);
        temp = temp->next;
    }
}
/* Code by GUDDU SHARMA */
void cal_TAT_WT_RT_SJF(struct Queue *q, int n)
{
    struct PCB *temp = q->front;
    for(int i=1; i<=n; i++)
    {
        if(temp->priority == i)
        {
            temp->turnaround_Time = (temp->completion_Time) - (temp->arrival_Time);
            temp->wait_Time = (temp->turnaround_Time) - (temp->total_burstTime);
            temp->response_Time = (temp->turnaround_Time) - (temp->total_burstTime);
        }
        else
        {
            while(temp->priority != i)
                temp = temp->next;
            temp->turnaround_Time = (temp->completion_Time) - (temp->arrival_Time);
            temp->wait_Time = (temp->turnaround_Time) - (temp->total_burstTime);
            temp->response_Time = (temp->turnaround_Time) - (temp->total_burstTime);
        }
        temp = q->front;
    }
}
void Gantt_chartFCFS(struct Queue *q, int n)
{
    int i, time;
    struct PCB *temp = q->front;
    struct PCB *temp2 = q->front;
    printf("\n\n\tGANTT CHART: \n");
    for(i=1; i<=n; i++)
        printf("----------------");
    printf("\n");
    for(i=1; i<=n; i++)
    {
        printf("|\tP%d\t", temp->process_no);
        temp = temp->next;
    }
    printf("|\n");
    for(i=1; i<=n; i++)
        printf("----------------");
    printf("\n0\t");
    time = 0;
    for(i=1; i<n; i++)
    {
        time = time + temp2->total_burstTime;
        printf("\t%d \t", time);
        temp2 = temp2->next;
    }
    time = time + temp2->total_burstTime;
    printf("%10d", time);
}
/* Code by GUDDU SHARMA */
void update_priority(struct Queue *q, int n)
{
	struct PCB *temp = q->front;
	int min = 35, count = 1;
	for(int i=0; i<n; i++)
	{
		min = 35;
		temp = q->front;
		while(temp != NULL)
		{
			if(temp->total_burstTime <= min && temp->priority == 0)
				min=temp->total_burstTime;
			temp=temp->next;
		}
		temp = q->front;
		while(temp != NULL)
		{
		    if(temp->arrival_Time == 0 && temp->priority == 0)
            {
                temp->priority = count;
                count++;
            }
			if(temp->total_burstTime == min && temp->priority == 0)
			{
				temp->priority = count;
				count++;
			}
			temp=temp->next;
		}
	}
}
/* Code by GUDDU SHARMA */
int giveNo_Time(struct Queue *q, int p, int c)
{
    struct PCB *temp = q->front;
    while(temp)
    {
        if(temp->priority == p && c == 1)
            return temp->process_no;
        if(temp->priority == p && c == 0)
            return temp->total_burstTime;
        temp = temp->next;
    }
}
/* Code by GUDDU SHARMA */
void Gantt_chartSJF(struct Queue *q, int n)
{
    int i, time = 0;
    struct PCB *temp = q->front;
    printf("\n\n\tGANTT CHART: \n");
    for(i=1; i<=n; i++)
        printf("----------------");
    printf("\n");
    for(i=1; i<=n; i++)
    {
        int id_ch = giveNo_Time(q, i, 1);
        printf("|\tP%d\t", id_ch);
    }
    printf("|\n");
    for(i=1; i<=n; i++)
        printf("----------------");
    printf("\n0\t");
    for(i=1; i<=n; i++)
    {
        time = time + giveNo_Time(q, i, 0);
        if(temp->priority == i)
            temp->completion_Time = time;
        else
        {
            while(temp->priority != i)
                temp = temp->next;
            temp->completion_Time = time;
        }
        if(i == n)
            printf("%10d", time);
        else
            printf("\t%d \t", time);
        temp = q->front;
    }
}
/* Code by GUDDU SHARMA */
int main()
{
    int n, i, id, cpb, iob, tb, art, prio = 0;
    char *sta;
    struct PCB *nsq = createProcess();
    printf("ENTER THE NO.OF PROCESSES: ");
    scanf("%d", &n);
    printf("\n");
    srand(time(0));
    for(i=1; i<=n; i++)
    {
        id = rand()%90000+100000;  //To have 6 digit UID
        cpb = rand()%9 + 1;
        iob = rand()%9 + 1;
        if(i == 1)
        {
            art = 0;
            cpb = 1;
            iob = 2;
        }
        else
            art = rand()%9;
        tb = cpb + iob;
        if(cpb > iob)
            sta = "CPU BOUND ";
        else
            sta = "I/O BOUND ";
        enQueue(nsq, i, id, cpb, iob, tb, art, sta, prio);
    }
    printf("\t\t\t\t\t[ B.T. = BURST TIME,\tA.T. = ARRIVAL TIME ]\n");
    printf("\t[ T.A.T. = TURN AROUND TIME = (COMPLETION TIME - ARRIVAL TIME),\t\tW.T. = WAITING TIME = (TURN AROUND TIME - BURST TIME) ]\n");
    printf("\t\t\t[ R.T. = RESPONSE TIME = (TIME AT WHICH THE PROCESS GETS THE CPU - ARRIVAL TIME) ]\n\n");
    printf("\nPROCESS NO   PROCESS ID   CPU B.T.   I/O B.T.   TOTAL B.T.   A.T.   STATUS\n\n");
    Print_PCB(nsq);
    cal_TAT_WT_RT_FCFS(nsq, n);
    printf("\n----------------------------------------------------FIRST COME FIRST SERVE---------------------------------------------------------------------------------");
    printf("\n\nPROCESS NO  TOTAL B.T.    A.T.   T.A.T.   W.T.   R.T. \n\n");
    Print_table_FCFS(nsq);
    Gantt_chartFCFS(nsq, n);
    printf("\n\n\n-------------------------------------------------------SHORTEST JOB FIRST-----------------------------------------------------------------------------------");
    update_priority(nsq, n);
    Gantt_chartSJF(nsq, n);
    cal_TAT_WT_RT_SJF(nsq, n);
    printf("\n\nPROCESS NO  TOTAL B.T.    A.T.   PRIORITY   T.A.T.   W.T.   R.T. \n\n");
    Print_table_SJF(nsq);
    return 0;
}
/* Code by GUDDU SHARMA */
