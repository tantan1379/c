#include <stdio.h>

struct TIME add(struct TIME now, struct TIME past);

struct TIME {
	int hour;
	int minute;
};

int main()
{
	struct TIME now = {1,50};
	struct TIME past = {1,20};
	struct TIME after;
	after=add(now, past);
	printf("%d:%d",after.hour,after.minute);

}

struct TIME add(struct TIME now, struct TIME past)
{
	struct TIME after;
	after.hour = (now.hour + past.hour+(now.minute+past.minute)/60);
	after.minute = (now.minute + past.minute) % 60;
	return after;
}
