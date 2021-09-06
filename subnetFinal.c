#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define IP_LEN 16
#define IP_PART_LEN 3
#define ARR_LEN 4
#define IP_AND_SUBNET 19
#define BIN_SUBNET 32
#define BYTE_LEN 8
#define MASK_NUM 2

void seperateIp(char * ipAndSub,char * ipaddr);

void seperatesubnetMask(char * ipAndSub,char * subnetMask);

void ipToArr(char * ip,int * arr);

void andBetweenIP(int * ip, int * subnet, int * result);

int checkIfEqual(int * result1, int * result2);

void printArr(int * arr);

void maskToArr(char * maskNum, int * arr);

void arrayToIp(int * arr, char * ipaddr);

int main(int argc, char ** argv)
{
    int subnetArr[ARR_LEN] = {0};
    int netArr[ARR_LEN] = {0};
    int ipArr[ARR_LEN] = {0};
    int netResult[ARR_LEN] = {0};
    int ipResult[ARR_LEN] = {0};
    char ip[IP_LEN] = "";
    char netIp[IP_LEN] = "";
    char ipAndSubnet[IP_AND_SUBNET] = "";
    char subnetMask[IP_LEN] = "";

    if (argc < 3)
    {
        printf("\n**********************************************************************\n\n");
        printf("[-] Required:\n\n[*]./subnet {[network address]/[subnet mask]} {[ip address]}\n\nOR:\n\n[*]./subnet {[network address]} {[subnet mask]} {[ip address]}\n");
        printf("\n**********************************************************************\n\n");
        return 1;
    }
    else if (argc == 3)
    {
        strncpy(ipAndSubnet, argv[1], IP_AND_SUBNET);
        strncpy(ip, argv[2], IP_LEN);

        if (strchr(ipAndSubnet, '/') == NULL)
        {
            printf("\n**********************************************************************\n\n");
        printf("[-] Invalid arguments passed !\n\nRequired:\n\n[*]./subnet {[network address]/[subnet mask]} {[ip address]}\n\nOR:\n\n[*]./subnet {[network address]} {[subnet mask]} {[ip address]}\n");
        printf("\n**********************************************************************\n\n");
        return 1;
        }
        
        seperateIp(ipAndSubnet, netIp);
        seperatesubnetMask(ipAndSubnet, subnetMask);

        maskToArr(subnetMask, subnetArr);
        strncpy(subnetMask, "", IP_LEN);
        arrayToIp(subnetArr, subnetMask);

        ipToArr(netIp, netArr);
        ipToArr(ip, ipArr);

        andBetweenIP(netArr, subnetArr, netResult);
        andBetweenIP(ipArr, subnetArr, ipResult);

    }
    else
    {
        strncpy(netIp, argv[1], IP_LEN);
        strncpy(subnetMask, argv[2], IP_LEN);
        strncpy(ip, argv[3], IP_LEN);


        ipToArr(netIp, netArr);
        ipToArr(subnetMask, subnetArr);
        ipToArr(ip, ipArr);

        andBetweenIP(netArr, subnetArr, netResult);
        andBetweenIP(ipArr, subnetArr, ipResult);
    }
    
   
    
    printf("[*] Network IP: %s\n[*] Subnet mask: %s\n[*] IP to check: %s\n",netIp, subnetMask, ip);

    printf("\n**********************************************************************\n\n");
    if (checkIfEqual(netResult, ipResult) == 0)
    {
        printf("[+] The ip address { %s } is in the network { %s }\n", ip, netIp);
    }
    else
    {
        printf("[-] The ip address { %s } is not in the network { %s }\n", ip, netIp);
    }
    printf("\n**********************************************************************\n\n");


    return 0;
}

void seperateIp(char * ipAndSub,char * ipaddr)
{
  for (int i = 0, j = 0; i < IP_LEN; i++)
    {

        if (ipAndSub[i] == '/')          
        {

            break;

        }

        else
        {
            ipaddr[j] = ipAndSub[i];
            j++;
        }
    }
}
void seperatesubnetMask(char * ipAndSub,char * subnetMask)
{
    int index = 0, i = 0;
    while (ipAndSub[index] != '/')
    {
        index ++;
    }
    index++;
   while (index < IP_AND_SUBNET)
   {
       subnetMask[i] = ipAndSub[index];
       i++;
       index++;
   }
   
    
}

void ipToArr(char * ip,int * arr)
{
    char tmp[IP_PART_LEN] = "";
    for (int i = 0, index = 0, j = 0; i < IP_LEN; i++)
    {
        if (ip[i] == '.' || i == IP_LEN - 1)
        {
            arr[index] = atoi(tmp);
            strncpy(tmp,"",IP_PART_LEN);
            j = 0;
            index++;
        }
        else
        {
            tmp[j] = ip[i];
            j++;
        }
        
    }
}

void maskToArr(char * maskNum, int * arr)
{
    int countOne = atoi(maskNum);
    int sum = 0;
    int counter = 0;
    int power = 7;
    int index = 0;
    char binMask[BIN_SUBNET] = "";

    for (int i = 0; i < BIN_SUBNET; i++)
    {
        if (countOne > 0)
        {
            binMask[i] = '1';
            countOne--;
        }
        else
        {
            binMask[i] = '0';
        }
    }
    for (int i = 0; i < BIN_SUBNET; i++)
    {
        if (binMask[i] == '1')
        {
            sum += (int)(pow(2,power));
        }
        counter++;
        power--;
        if (counter == BYTE_LEN)
        {
            arr[index] = sum;
            sum = 0;
            counter = 0;
            power = 7;
            index++;
        }
        
    }
    
    
}
void andBetweenIP(int * ip, int * subnet, int * result)
{
    
    for (int i = 0; i < ARR_LEN; i++)
    {
        result[i] = ip[i] & subnet[i];
    }
}

int checkIfEqual(int * result1, int * result2)
{
    for (int i = 0; i < ARR_LEN; i++)
    {
        if (result1[i] != result2[i])
        {       
            return 1;
        }
        
    }
    return 0;
}

void printArr(int * arr)
{
    for (int i = 0; i < ARR_LEN; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void arrayToIp(int * arr, char * ipaddr)
{
    char tmp[ARR_LEN] = "";
    char dot[1] = ".";

    for (int i = 0; i < ARR_LEN; i++)
    {
        sprintf(tmp, "%d", arr[i]);
        strncat(ipaddr, tmp, IP_PART_LEN);
        if (i != ARR_LEN-1)
        {
            strncat(ipaddr, dot, 1);
        }
    }
}
