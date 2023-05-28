/*
Name: Necati
Surname: Kocak
Number: 150120053
Purpose the program:The purpose of the program is to identify lines and stations
in the metro system. Then it is to show the user the best path between the desired stations.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10
typedef struct //We create the struct
{

    char name[20]; //We define variables.
    double x,y;

} MetroStation;


typedef struct //We create the struct
{

    char color[20]; //We define variables.
    MetroStation MetroStations[SIZE];

} MetroLine;


typedef struct //We create the struct
{

    char name[20];//We define variables.
    MetroLine MetroLines[SIZE];

} MetroSystem;

//Declare a MetroSystem with the name of istanbul and an empty content.
MetroSystem istanbul = {"istanbul", '\0'};

 // MetroStation findNearestStation (MetroSystem system, double x, double y);




int equals(MetroStation s1, MetroStation s2) //In this function, if the names of s1 and s2 MetroStations are the same,
// we return 1, otherwise we return 0.
{

    if(strcmp(s1.name,s2.name)==0)
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

void addStation(MetroLine *line, MetroStation station) /*We return the while with SIZE and if it comes to an empty metro station,
 we exit the loop and add the entered MetroStation to the MetroLine received as a pointer.*/
{

    int i=0;
    while(i<SIZE)
    {
        if(line->MetroStations[i].name[0]=='\0')
        {
            break;
        }
        i++;
    }
    line->MetroStations[i]=station;

}

int hasStation(MetroLine line, MetroStation station)/*
hasStation function returns 1, returns 0 if the entered metro station is on the entered line
*/{
    for(int i=0; i<SIZE; i++)
    {
        if(strcmp(line.MetroStations[i].name,station.name)==0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}


MetroStation getFirstStop(MetroLine line)/*
If the first stop on the entered line is empty, it returns an empty metrostation;
 otherwise, it returns the first metrostation.
*/
{
    if(strcmp(line.MetroStations[0].name[0],'\0'))
    {
        MetroStation sta;
        return sta;
    }
    else
    {
        return line.MetroStations[0];
    }

}

MetroStation getPreviousStop(MetroLine line,MetroStation sta)/*We turn each station. If the entered station is on the entered line,
 it enters if, and if the first stop is the entered station, it returns an empty metroStation.
 If not, the previous station of the current i value is returned.
*/
{
    for(int i=0; i<SIZE; i++)
    {
        if(hasStation(line,sta)==1)
        {
            if(strcmp(getFirstStop(line).name,sta.name))
            {
                MetroStation free;
                return free;
            }
            else
            {
                return line.MetroStations[i-1];
            }
        }
    }
}

MetroStation getNextStop(MetroLine line,MetroStation sta) /*
We turn each station. If the entered station is on the entered line, it enters if,
if the entered line (SIZE -1). returns an empty metroStation if stop is the entered station.
If not, the next station of the current i value is returned.
*/
{
    if(hasStation(line,sta)==1)
    {
        for(int i=0; i<SIZE; i++)
        {
            if(strcmp(line.MetroStations[SIZE-1].name,sta.name))
            {
                MetroStation free;
                return free;
            }
            else
            {
                return line.MetroStations[i+1];
            }

        }


    }
}

void addLine(MetroSystem *city, MetroLine line)/*
We return every line of the metro system entered as a pointer,
if that line is empty, we exit the loop and add it to the entered line.
*/

{

    int i=0;
    while(i<SIZE)
    {

        if(city->MetroLines[i].color[0]=='\0')
        {
            strcpy(city->MetroLines[i].color,line.color);
            city->MetroLines[i] = line;
            break;
        }
        i++;
    }
}
void printLine(MetroLine line)/*We write the color of the first line entered with this function.
 Then we check if the line is empty. Then we write the first station and loop it as much as the size of the line array,
 until the last station we write it as ", station name".
 The last station is "station name." We write as.
*/

{
    int i=1;
    printf("Metroline %s: ",line.color);
    if(line.MetroStations[0].name[0]!='\0')
    {
        printf("%s ",line.MetroStations[i-1].name);
        for(i=1; i<SIZE; i++)
        {
            if(line.MetroStations[i].name[0]=='\0')
            {
                printf(".\n");
                break;
            }
            else
            {
                printf(", %s",line.MetroStations[i].name);
            }
        }

    }
    else
    {
        printf("\nEmpty Line!!");
    }
}


void printPath(MetroStation stations[])
//With this function, we write the names of the stations entered as an array in order.
{
    if(stations[0].name[0]!='0')
    {
        printf("\t\t 1. %s \n",stations[0].name);
        for(int i = 1; i<SIZE; i++)
        {
            {
                if(stations[i].name[0]=='\0')
                {
                    break;
                }
                else
                {
                    printf("\t\t %d. %s\n",i+1,stations[i].name);
                }
            }
        }

    }

}

double getDistanceTravelled(MetroStation station[])
/*
With this function, we calculate the distances between the stations entered as a
series and equalize the distance variable.
*/
{

    double distance=0;
    for(int i=1; i<SIZE; i++)
    {
        if(station[i-1].name[0]=='\0')
        {
            break;
        }
        else
        {
            distance += sqrt(pow((station[i].x-station[i-1].x),2)+pow((station[i].y-station[i-1].y),2));
        }
    }
}



MetroStation findNearestStation(MetroSystem city, double x, double y)
/*We find a distance by calculating the distance between two points, another entered x and y values to the metrosystem entered with this function.
We rotate them until each MetroLine and each MetroStation is empty and we calculate the distance according to the x and y values of the current stations.
If the later calculated distance is less than the previous distance, we set that distance to min_distance and find the current i and j values.
When we find the shortest distance, we return the station corresponding to the i and j values we obtained.
*/
    {

        double distance=0, min_x, min_y, min_distance;
        int min_i= 0;
        int min_j = 0;

        min_x=city.MetroLines[0].MetroStations[0].x-x;
        min_y=city.MetroLines[0].MetroStations[0].y-y;
        min_distance = sqrt(pow((min_x),2)+pow((min_y),2));

        for(int i = 0 ; i<SIZE; i++)
        {
            if(city.MetroLines[i].color[0]=='\0')
            {
                break;
            }
            for(int j=1; j<SIZE; j++)
            {
                if(city.MetroLines[i].MetroStations[j].name[0]=='\0')
                {
                    break;
                }
                min_x=city.MetroLines[i].MetroStations[j].x-x;
                min_y=city.MetroLines[i].MetroStations[j].y-y;
                distance= sqrt(pow((min_x),2)+pow((min_y),2));
                if(distance<min_distance)
                {

                    min_distance=distance;
                    min_i=i;
                    min_j=j;
                }
            }
        }
        return city.MetroLines[min_i].MetroStations[min_j];
    }

void getNeighboringStations (MetroSystem system, MetroStation station, MetroStation *neighboringStations)
/*We return Lines until the MetroLine in the MetroSystem entered in this function is empty.
In that loop, we turn the Stations until the name of the MetroStations is empty.
We enter if unless the name of the entered station is equal to the current station name. If the station in the neighboringStations
array does not contain the MetroStation[j-1] and MetroStation[j+1] values of the current metroLine[i], we assign the stations to the
neighboringStations array. If not, we assign MetroStation[j+1] to the array. At the same time, we increase the count variable.
*/
{
   int i, j, count = 0;

   for (i = 0; strlen(system.MetroLines[i].color) != 0; i++)
   {
       for (j = 0; strlen(system.MetroLines[i].MetroStations[j].name) != 0; j++)
       {
           if (!strcmp(station.name, system.MetroLines[i].MetroStations[j].name))
           {
               if (!include(neighboringStations, system.MetroLines[i].MetroStations[j-1].name) && !include(neighboringStations, system.MetroLines[i].MetroStations[j+1].name)) {
                   if (j > 0)
                   {
                       neighboringStations[count++] = system.MetroLines[i].MetroStations[j - 1];
                       neighboringStations[count++] = system.MetroLines[i].MetroStations[j + 1];
                   }
                   else
                   {
                       neighboringStations[count++] = system.MetroLines[i].MetroStations[j + 1];
                   }

               }
           }
       }
   }
}

int include (MetroStation *array, MetroStation station)
//If the entered array contains the station, it returns 1, otherwise it returns 0.
{
   int i;
   for (i = 0; i < strlen(array[i].name) != 0; i++)
   {
       if (!strcmp(array[i].name, station.name))
       {
           return 1;
       }

   }
   return 0;
}

void findPath (MetroStation start, MetroStation finish, MetroStation *path)
//We get the start and finish stations and the path pointer. Inside the function,
//we create an empty metroStation array called partialpath of size SIZE
//and inside we call the recursiveFindePath function.
{
   MetroStation partialPath[SIZE] = {'\0'};


   recursiveFindPath(start, finish, path, partialPath);
}

void recursiveFindPath (MetroStation start, MetroStation finish, MetroStation *partialPath, MetroStation *bestPath)
/*
We are creating a function that takes a start and finish metro station named recursiveFindPath and takes a MetroStation pointer named bestpath and partialpath.
 We put the start and finish in the if in the partialpath array separately until we find it.
 We assign the values in partialPath to the bestPath array but i could not this function so this function is not working properly.
*/
{
   int i;
   double distance = 10000;

   for (i = 0; i < SIZE; i++)
   {
       if (equals(partialPath[i], start))
           return;
   }

   if (equals(start, finish))
   {
       for (i = 0; i < SIZE; i++)
       {
           if (strlen(partialPath[i].name) < 5)
           {
               partialPath[i] = finish;
               break;
           }
       }
       for (i = 0; strlen(partialPath[i].name) != 0; i++)
       {
           strcpy(bestPath[i].name, partialPath[i].name);
           bestPath[i].x = partialPath[i].x;
           bestPath[i].y = partialPath[i].y;
       }

       return;
   }



   MetroStation neighbors[SIZE] = {'\0'};
   getNeighboringStations(istanbul, start, neighbors);

   MetroStation duplicatePath[SIZE] = {'\0'};
   for (i = 0; strlen(partialPath[i].name) != 0; i++)
   {
       strcpy(duplicatePath[i].name, partialPath[i].name);
       duplicatePath[i].x = partialPath[i].x;
       duplicatePath[i].y = partialPath[i].y;
   }

   for (i = 0; i < SIZE; i++)
   {
           if (strlen(duplicatePath[i].name) < 5)
           {
               duplicatePath[i] = start;
               break;
           }
       }

   for (i = 0; strlen(neighbors[i].name) != 0; i++)
   {
       if (!include(duplicatePath, neighbors[i]))
       {
           recursiveFindPath(neighbors[i], finish, duplicatePath, partialPath);
       }
       else
       {
           recursiveFindPath(neighbors[i+1], finish, duplicatePath, partialPath);
           i++;
       }

   }

   for (i = 0; strlen(duplicatePath[i].name) != 0; i++)
   {
       strcpy(partialPath[i].name, duplicatePath[i].name);
       partialPath[i].x = duplicatePath[i].x;
       partialPath[i].y = duplicatePath[i].y;
   }

   if (strlen(partialPath[0].name) != 0)
   {
       if (getDistanceTravelled(partialPath) < getDistanceTravelled(bestPath)) //***
       {
               *bestPath = *partialPath;
       }
   }
}
int main()
{
   int i;
    double myX=1, myY=2;
    double goalX=62, goalY=45;

   // define 3 metro lines, 9 metro stations, and an empty myPath
   MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
   MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
   MetroStation myPath[SIZE]={'\0'};

   strcpy(red.color, "red");
   strcpy(blue.color, "blue");
   strcpy(green.color, "green");


   strcpy(s1.name, "Haydarpasa");        s1.x=0;    s1.y=0;
   strcpy(s2.name, "Sogutlucesme");    s2.x=10;    s2.y=5;
   strcpy(s3.name, "Goztepe");        s3.x=20;    s3.y=10;
   strcpy(s4.name, "Kozyatagi");        s4.x=30;    s4.y=35;
   strcpy(s5.name, "Bostanci");        s5.x=45;    s5.y=20;
   strcpy(s6.name, "Kartal");            s6.x=55;    s6.y=20;
   strcpy(s7.name, "Samandira");        s7.x=60;    s7.y=40;
   strcpy(s8.name, "Icmeler");        s8.x=70;    s8.y=15;

   //Add several metro stations to the given metro lines.
   addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);

   addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);

   addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);

   // Add red, blue, green metro lines to the Istanbul metro system.
   addLine(&istanbul, red);
   addLine(&istanbul, blue);
   addLine(&istanbul, green);

   // print the content of the red, blue, green metro lines
   printLine(red);
   printLine(blue);
   printLine(green);


   // find the nearest stations to the current and target locations
   MetroStation nearMe = findNearestStation(istanbul, myX, myY);
   MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

   printf("\n");

   printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

   // if the nearest current and target stations are the same, then print a message and exit.
   if(equals(nearMe, nearGoal)){
       printf("It is better to walk!\n");
       return 0;
   }

   // Calculate and print the myPath with the minimum distance travelled from start to target stations.
   findPath(nearMe, nearGoal, myPath);

   if(strlen(myPath[0].name) == 0)
       printf("There is no path on the metro!\n");
   else{
       printPath(myPath);
   }

   return 0;

}
