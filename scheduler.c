#include <stdio.h>
#include <stdbool.h>

struct Process {
    	int pid;
    	int arrival_time;
    	int burst_time;
    	int waiting_time;
    	int turnaround_time;
    	int response_time;
    	int completion_time;
    	bool completed;
};

void printTable(struct Process p[], int n) {
    	printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    	for (int i = 0; i < n; i++) {
        	printf("%d\t%d\t%d\t%d\t%d\t%d\n",
              		p[i].pid,
               		p[i].arrival_time,
               		p[i].burst_time,
               		p[i].waiting_time,
               		p[i].turnaround_time,
               		p[i].response_time);
    	}
}

void FCFS(struct Process p[], int n) {
    	printf("\n--- First Come First Served (FCFS) ---\n");

    	for (int i = 0; i < n - 1; i++) {
        	for (int j = 0; j < n - i - 1; j++) {
            		if (p[j].arrival_time > p[j + 1].arrival_time) {
                		struct Process temp = p[j];
                		p[j] = p[j + 1];
                		p[j + 1] = temp;
            		}
        	}
    	}
	int current_time = 0;
    	float total_wt = 0, total_tat = 0, total_rt = 0;
	

	printf("Gantt Chart: ");
    	for (int i = 0; i < n; i++) {
		if(current_time < p[i].arrival_time){
			current_time = p[i].arrival_time;
		}

		printf("| P%d ", p[i].pid);
		p[i].response_time = current_time - p[i].arrival_time;
        	p[i].waiting_time = current_time - p[i].arrival_time;
        	current_time += p[i].burst_time;
        	p[i].completion_time = current_time;
        	p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
		//p[i].complated = true;
        	total_wt += p[i].waiting_time;
        	total_tat += p[i].turnaround_time;
        	total_rt += p[i].response_time;

    	}
    	printf("|\n");

    	printTable(p, n);
    	printf("\nAverage Waiting Time: %.2f", total_wt / n);
    	printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    	printf("\nAverage Response Time: %.2f\n", total_rt / n);
}



void SJF(struct Process p[], int n) {
    	printf("\n=== Shortest Job First (SJF) ===\n");

    	int completed = 0, current_time = 0;
    	float total_wt = 0, total_tat = 0, total_rt = 0;

    	for (int i = 0; i < n; i++) p[i].completed = false;

    	printf("Gantt Chart: ");
    	while (completed != n) {
        	int idx = -1;
        	int min_bt = 9999;

       	
        	for (int i = 0; i < n; i++) {
            		if (!p[i].completed && p[i].arrival_time <= current_time) {
                		if (p[i].burst_time < min_bt) {
                    			min_bt = p[i].burst_time;
                    			idx = i;
                		} else if (p[i].burst_time == min_bt && p[i].arrival_time < p[idx].arrival_time) {
                    			idx = i;
                		}
            		}		
        	}

        	printf("| P%d ", p[idx].pid);

        	p[idx].response_time = current_time - p[idx].arrival_time;
        	p[idx].waiting_time = p[idx].response_time;
        	current_time += p[idx].burst_time;
        	p[idx].completion_time = current_time;
        	p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;

        	total_wt += p[idx].waiting_time;
        	total_tat += p[idx].turnaround_time;
        	total_rt += p[idx].response_time;

        	p[idx].completed = true;
        	completed++;
    	}
    	printf("|\n");

    	printTable(p, n);
    	printf("\nAverage Waiting Time: %.2f", total_wt / n);
    	printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    	printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

int main(){
	int n;
    	printf("Enter the number of processes: ");
    	scanf("%d", &n);
        struct Process p[n], copy[n];

	for (int i = 0; i < n; i++) {
        	p[i].pid = i + 1;
        	printf("Enter the arrival time and burst time for process %d: ", i + 1);
        	scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        	copy[i] = p[i];
    	}
	 FCFS(p, n);
    	SJF(copy, n);
	return 0;
}
