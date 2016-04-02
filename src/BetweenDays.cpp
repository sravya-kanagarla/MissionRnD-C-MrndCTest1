/*
Q4: Two dates are given in a 8 node single linked list form,where each node
has one digit only, dates 01-31, months 01-12, year 0000-9999.

Find the number of days in between those two dates .[Exclusive]

Ex : Date1:  0->1->0->1->2->0->0->4 .
     Date2 : 0->5->0->1->2->0->0->4 should return 3 .
As there are 3 days between Jan1st 2004 and Jan 5th 2004.

Ex 2 : Date1 : 3->1->1->2->2->0->1->2.
       Date2 : 0->2->0->1->2->0->1->3 should return 1 .
(There is only one day between 31st Dec 2012 and 2nd  Jan 2013 .)

Note : Consecutive Days and Same Days should return 0;
->Return -1 for NULL Inputs .
->Between Days have to be calculated by not including start and end date .
->The SLL will have 8 Nodes in all cases . Month 9 will be represented as 09.

Difficulty : Hard 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node{
	int data;
	struct node *next;
};

int validate(int day, int mon, int year) {
	int i;
	for (i = 0; year > 0; i++)
		year /= 10;
	if (i != 4)
		return 1;
	if (mon < 1 || mon > 12) {
		return 1;
	}
	else {
		int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ((i % 400 == 0) || ((i % 100 != 0) && (i % 4 == 0)))
			daysInMonth[1] = 29;
		if (day < 0 || day > daysInMonth[mon - 1])
			return 1;
	}
	return 0;
}

int countDaysOfYears(int year1, int year2) {
	int days = 0;
	int i;
	for (i = year1 + 1; i < year2; i++) {
		days += 365;
		if ((i % 400 == 0) || ((i % 100 != 0) && (i % 4 == 0)))
			days += 1;
	}
	return days;
}

int between_days(struct node *date1head, struct node *date2head){
	if (date1head == NULL || date2head == NULL)
		return -1;
	int date1 = (date1head -> data) * 10 + (date1head->next->data);
	int date2 = (date2head->data) * 10 + (date2head->next->data);
	date1head = date1head->next->next;
	date2head = date2head->next->next;
	int month1 = (date1head->data) * 10 + (date1head->next->data);
	int month2 = (date2head->data) * 10 + (date2head->next->data);
	date1head = date1head->next->next;
	date2head = date2head->next->next;
	int year1 = (date1head->data) * 1000 + (date1head->next->data) * 100 + (date1head->next->next->data) * 10 + (date1head->next->next->next->data);
	int year2 = (date2head->data) * 1000 + (date2head->next->data) * 100 + (date2head->next->next->data) * 10 + (date2head->next->next->next->data);
	if (validate(date1, month1, year1) || validate(date2, month2, year2) || year1 > year2)
		return -1;
	int days = countDaysOfYears(year1, year2);
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year1 == year2) {
		if (month1 > month2)
			return -1;
		else if (month1 == month2) {
			date1++;
			while (date1 < date2) {
				days++;
				date1++;
			}
		}
		else {
			if ((year1 % 400 == 0) || ((year1 % 100 != 0) && (year1 % 4 == 0)))
				daysInMonth[1] = 29;
			days += (daysInMonth[month1 - 1] - date1);
			days += date2 - 1;
			month1++;
			while (month1 < month2) {
				days += daysInMonth[month1 - 1];
				month1++;
			}
		}
	}
	else {
		if ((year1 % 400 == 0) || ((year1 % 100 != 0) && (year1 % 4 == 0)))
			if (month1 <= 2)
				days += 1;
		days += (daysInMonth[month1 - 1] - date1);
		month1++;
		while (month1 <= 12) {
			days += daysInMonth[month1 - 1];
			month1++;
		}
		if ((year2 % 400 == 0) || ((year2 % 100 != 0) && (year2 % 4 == 0)))
			if (month2 > 2)
				days += 1;
		days += date2 - 1;
		month2--;
		while (month2 > 0) {
			days += daysInMonth[month1 - 1];
			month2--;
		}
	}
	return days;
}