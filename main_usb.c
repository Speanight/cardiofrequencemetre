#include <ftd2xx.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FT_STATUS ftStatus;
    DWORD numDevs;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
// create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus == FT_OK) {
        printf("Number of devices is %d\n",numDevs);
    }
    if (numDevs > 0) {
// allocate storage for list based on numDevs
        devInfo =
                (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
// get the device information list
        ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
        if (ftStatus == FT_OK) {
            for (int i = 0; i < numDevs; i++) {
                printf("Dev %d:\n",i);
                printf(" Flags=0x%x\n",devInfo[i].Flags);
                printf(" Type=0x%x\n",devInfo[i].Type);
                printf(" ID=0x%x\n",devInfo[i].ID);
                printf(" LocId=0x%x\n",devInfo[i].LocId);
                printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
                printf(" Description=%s\n",devInfo[i].Description);
                printf(" ftHandle=0x%x\n", devInfo[i].ftHandle);
            }
        }
    }

    // Trying to open the device.
    FT_HANDLE ftHandle;
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus == FT_OK) {
        printf("Device is open!\n");
    }
    else {
        printf("Error: device is not open.\n");
    }


    // Closes the device.
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(0,&ftHandle);
    if (ftStatus == FT_OK) {
        // FT_Open OK, use ftHandle to access device
        // when finished, call FT_Close
        FT_Close(ftHandle);
    }
    else {
        // FT_Open failed
    }


    return 0;
}