#include<stdio.h>
#include <time.h>

int main()
{
   time_t now;
   struct tm* tm;
   time_t start;
   now = time(0);
   tm = localtime(&now);
   printf("Hour : %d\nMinute : %d\nSecond : %d\n",tm->tm_hour,tm->tm_min,tm->tm_sec);
   start = mktime(tm);

   time_t rawtime;

   time ( &rawtime );
   printf ( "The current local time is: %s", ctime (&rawtime) );
   // see time.h for structure tm members

   //return 0;

	/* mktime example: weekday calculator */

	  //time_t rawtime;
	  struct tm * timeinfo;
	  int year, month ,day;
	  char * weekday[] = { "Sunday", "Monday",
	                       "Tuesday", "Wednesday",
	                       "Thursday", "Friday", "Saturday"};

	  /* prompt user for date */
	  printf ("Enter year: "); scanf ("%d",&year);
	  printf ("Enter month: "); scanf ("%d",&month);
	  printf ("Enter day: "); scanf ("%d",&day);

	  /* get current timeinfo and modify it to the user's choice */
	  time ( &rawtime );
	  timeinfo = localtime ( &rawtime );
	  timeinfo->tm_year = year - 1900;
	  timeinfo->tm_mon = month - 1;
	  timeinfo->tm_mday = day;

	  /* call mktime: timeinfo->tm_wday will be set */
	  mktime ( timeinfo );

	  printf ("That day is a %s.\n", weekday[timeinfo->tm_wday]);

	  return 0;

}
