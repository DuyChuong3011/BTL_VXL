#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_counter1;
extern int timer_counter2;
extern int timer_counter3;
extern int timer_counter4;

extern int flag1;
extern int flag2;
extern int flag3;
extern int flag4;
extern int timer_cycle;

void setTimer1(int n);
void setTimer2(int n);
void setTimer3(int n);
void setTimer4(int n);

void timer_run1();
void timer_run2();
void timer_run3();
void timer_run4();

void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
