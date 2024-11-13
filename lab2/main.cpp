#include <cstdio>
#include <iostream>

class window
{
public:
    int window_next_available_times;
    int window_served_counts;
    int window_number;
    window* next = nullptr;
    window()
    {
        window_next_available_times = 0;
        window_served_counts = 0;
    }
};

class customer
{
public:
    int arrival_times;
    int process_times;
    customer* next = nullptr;
    customer(int x,int y)
    {
        arrival_times = x;
        process_times = y;
    }
};
using namespace std;
int main() {
    int total_wait_time = 0;
    int max_wait_time = 0;
    int last_finish_time = 0;
    int customer_total = 0;
    int window_total = 0;
    cin>>customer_total;
    customer* customer_head = new customer(0,0); customer_head = nullptr;

    //构建顾客队列
    for (size_t i = 0; i < customer_total; i++)
    {
        int x = 0,y = 0;
        cin>>x>>y;
        customer* temp = new customer(x,y);
        if (customer_head == nullptr)
        {
            customer_head = temp;
        }
        else
        {
            customer* temp2 = customer_head;
            while (temp2->next != nullptr)
            {
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }
    }
    
    cin>>window_total;
    window* window_head = new window; window_head = nullptr;
    
    // 构建窗口链表
    for (int i = 0; i < window_total; i++) 
    {
        window* temp = new window;
        temp->window_number = i; // 赋予窗口编号
        if (window_head == nullptr) {
        window_head = temp;
        } 
        else {
        window* temp2 = window_head;
        while (temp2->next != nullptr) {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

    customer* current_customer = customer_head;
    while (current_customer != nullptr) {
        int arrival_time = current_customer->arrival_times;
        int process_time = current_customer->process_times;

        // 查找在顾客到达时可用的窗口
        window* available_window = nullptr;
        window* temp_window = window_head;
        int min_window_number = window_total; // 初始化为最大编号
        while (temp_window != nullptr) {
            if (temp_window->window_next_available_times <= arrival_time) {
                if (temp_window->window_number < min_window_number) {
                    min_window_number = temp_window->window_number;
                    available_window = temp_window;
                }
            }
            temp_window = temp_window->next;
        }

        int wait_time = 0;
        window* selected_window = nullptr;

        if (available_window != nullptr) {
            // 有可用窗口
            selected_window = available_window;
            wait_time = 0;
            selected_window->window_next_available_times = arrival_time + process_time;
        } else {
            // 没有可用窗口，选择下一可用时间最早的窗口
            int earliest_available_time = INT_MAX;
            temp_window = window_head;
            while (temp_window != nullptr) {
                if (temp_window->window_next_available_times < earliest_available_time) {
                    earliest_available_time = temp_window->window_next_available_times;
                    min_window_number = temp_window->window_number;
                    selected_window = temp_window;
                } else if (temp_window->window_next_available_times == earliest_available_time) {
                    // 可用时间相同，选择编号最小的窗口
                    if (temp_window->window_number < min_window_number) {
                        min_window_number = temp_window->window_number;
                        selected_window = temp_window;
                    }
                }
                temp_window = temp_window->next;
            }
            wait_time = selected_window->window_next_available_times - arrival_time;
            selected_window->window_next_available_times += process_time;
        }

        // 更新窗口的服务计数
        selected_window->window_served_counts++;

        // 更新统计信息
        total_wait_time += wait_time;
        if (wait_time > max_wait_time) {
            max_wait_time = wait_time;
        }
        int finish_time = arrival_time + wait_time + process_time;
        if (finish_time > last_finish_time) {
            last_finish_time = finish_time;
        }

        // 处理下一个顾客
        current_customer = current_customer->next;
    }

    double average_wait_time = static_cast<double>(total_wait_time) / customer_total + 1e-8; // 加上小数防止精度问题
    printf("%.1f %d %d\n", average_wait_time, max_wait_time, last_finish_time);

    // 输出每个窗口服务的顾客数量
    window* temp_window = window_head;
    while (temp_window != nullptr) {
        printf("%d", temp_window->window_served_counts);
        if (temp_window->next != nullptr) {
            printf(" ");
        }
        temp_window = temp_window->next;
    }
    printf("\n");
    cout<<"hello world";
    return 0;
}
