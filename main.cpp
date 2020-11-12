#include <iostream>
#include <iomanip>
#include <pcap.h>

using namespace std;

#define PROMISCUOUS 1


void printLine()
{
    cout<<"-----------------------------------------------"<<endl;
}

void printByHexData(u_int8_t *printArr, int length)
{

    for(int i=0;i<length;i++)
    {
        if(i%16==0)
            cout<<endl;
        cout<<setfill('0');
        cout<<setw(2)<<hex<<(int)printArr[i]<<" ";

    }

    cout<<dec<<endl;
    printLine();
}


int main(int argc, char* argv[])
{

    char* device = argv[1];

    char err_buf[PCAP_ERRBUF_SIZE];
    pcap_t *pcd;

    if((pcd = pcap_open_live(device,BUFSIZ,PROMISCUOUS,1,err_buf))==NULL)
    {
        perror(err_buf);
        exit(1);
    }

    uint8_t packet[100]; //fill packet as follow network protocol (e.g., ethernet header > ip header > whatever...)
    memset(packet, 0, sizeof(packet));
    int size_of_packet = sizeof(packet);

    pcap_sendpacket(pcd, packet, size_of_packet);

    return 0;
}
