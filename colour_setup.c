/*******************************************************
 Windows HID simplification

 Alan Ott
 Signal 11 Software

 8/22/2009

 Copyright 2009

 This contents of this file may be used by anyone
 for any reason without any conditions and may be
 used as a starting point for your own applications
 which use HIDAPI.
********************************************************/

#include <stdio.h>
#include <wchar.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
#include <unistd.h>

#include <colour_setups.h>

#define MAX_STR 255

void list_modes(void)
{
    printf("Modes available:\n");
    printf(" 0: Black\n");
    printf(" 1: Default\n");
    printf(" 2: Red\n");
    printf(" 3: Blue\n");
    printf(" 4: Ripple 1\n");
    printf(" 5: Ripple 2\n");
    printf(" 6: Ripple 3\n");
    printf(" 7: Ripple 4\n");
    printf(" 8: Ripple 5\n");
    printf(" 9: Ripple 6\n");
}

int main(int argc, char* argv[])
{
	int i;
	int res;
    int mode = 0;
    int verbose = 0;
    int opt;
	unsigned char buf[256];
	struct hid_device_info *devs, *cur_dev;
	wchar_t wstr[MAX_STR];
    char path_buf[64];
	hid_device *handle;

    while ((opt = getopt(argc, argv, "vhL")) != -1) {
        switch (opt) {
            case 'v':
                verbose++;
                break;
            case 'L':
                list_modes();
                exit(0);
                break;
            case 'h':
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-v] [-L] <mode>\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (argv[optind]) {
        mode = atoi(argv[optind]);
    } else {
        fprintf(stderr, "No mode provided\n");
        exit(EXIT_FAILURE);
    }

	if (hid_init()) {
		return -1;
    }

	devs = hid_enumerate(0x03f0, 0x1f41);

	cur_dev = devs;
	while (cur_dev) {
        if (verbose) {
            printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
                   cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
            printf("\n");
            printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
            printf("  Product:      %ls\n", cur_dev->product_string);
            printf("  Release:      %hx\n", cur_dev->release_number);
            printf("  Interface:    %d\n",  cur_dev->interface_number);
            printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
            printf("\n");
        }
        strcpy(path_buf, cur_dev->path);
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	// Set up the command buffer.
	memset(buf,0x00,sizeof(buf));
	buf[0] = 0x01;
	buf[1] = 0x81;

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open_path(path_buf);
	if (!handle) {
		printf("unable to open device %s\n", path_buf);
 		return 1;
	}

	// Read the Manufacturer String
	wstr[0] = 0x0000;
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	if (res < 0) {
		printf("Unable to read manufacturer string\n");
    }
    if (verbose) {
        printf("Manufacturer String: %ls\n", wstr);
    }

	// Read the Product String
	wstr[0] = 0x0000;
	res = hid_get_product_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read product string\n");
    if (verbose) {
        printf("Product String: %ls\n", wstr);
    }

    const uint8_t *p=0;
    int p_len = 0;
    switch (mode) {
        case 0: {
            printf("  0: Black\n");
            p=(const uint8_t*)mode_black;p_len = sizeof(mode_black)/64;
            break;
        }
        case 1: {
            printf("  1: Default\n");
            p=(const uint8_t*)mode_def;p_len = sizeof(mode_def)/64;
            break;
        }
        case 2: {
            printf("  2: Red\n");
            p=(const uint8_t*)mode_red;p_len = sizeof(mode_red)/64;
            break;
        }
        case 3: {
            printf("  3: Blue\n");
            p=(const uint8_t*)mode_blue;p_len = sizeof(mode_blue)/64;
            break;
        }
        case 4: {
            printf("  4: Ripple\n");
            p=(const uint8_t*)mode_ripple_0;p_len = sizeof(mode_ripple_0)/64;
            break;
        }
        case 5: {
            printf("  5: Ripple\n");
            p=(const uint8_t*)mode_ripple_1;p_len = sizeof(mode_ripple_1)/64;
            break;
        }
        case 6: {
            printf("  6: Ripple\n");
            p=(const uint8_t*)mode_ripple_2;p_len = sizeof(mode_ripple_2)/64;
            break;
        }
        case 7: {
            printf("  7: Ripple\n");
            p=(const uint8_t*)mode_ripple_3;p_len = sizeof(mode_ripple_3)/64;
            break;
        }
        case 8: {
            printf("  8: Ripple\n");
            p=(const uint8_t*)mode_ripple_4;p_len = sizeof(mode_ripple_4)/64;
            break;
        }
        case 9: {
            printf("  9: Ripple\n");
            p=(const uint8_t*)mode_ripple_5;p_len = sizeof(mode_ripple_5)/64;
            break;
        }
    }

    if (p) {
        for (i=0;i<p_len;i++) {
            res = hid_write(handle, &p[i*64], 64);
            if (res < 0) {
                printf("Unable to write() (2)\n");
            }
        }
    }
	hid_close(handle);

	/* Free static HIDAPI objects. */
	hid_exit();

	return 0;
}
