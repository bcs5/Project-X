#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LED Driver");
MODULE_AUTHOR("GGML");

// inode strucuture: sends info to the kernel about the major and minor number
// filp structure: information relative to the different ops that can be performed on a file

void dbg() {
  printk("<1> On here\n");
}

int led_device_open(struct inode *inode, struct file *filp);
int led_device_release(struct inode *inode, struct file *filp);
ssize_t led_device_read(struct file *filp, char *buffer, size_t count, loff_t *f_pos);
ssize_t led_device_write(struct file* filp, char *buffer, size_t count, loff_t *f_pos);
int led_device_init(void);
void led_device_exit(void);

struct file_operations led_device_fops = {
    read: led_device_read,
    write: led_device_write,
    open: led_device_open,
    release: led_device_release
};

int led_device_major = 61;
int LED_ADDRESS = 0XC080;

int led_device_open(struct inode *inode, struct file *filp) {
    // initialize driver variables or reset the device
    return 0;
}

int led_device_release(struct inode *inode, struct file *filp) {
    //closing a file in user space - free the used memory and variables related to the opening of the device
    return 0;
}

ssize_t led_device_read(struct file *filp, char *buffer, size_t count, loff_t *f_pos) {
    // similar to FREAD. f_pos = position of where to start reading the file
    char led_temp_buffer;

    led_temp_buffer = inb(LED_ADDRESS);

    copy_to_user(buffer, &led_temp_buffer, 1); // grabs a single byte from the driver buffer

    // changing reading position as best suits
    if (*f_pos == 0) {
        *f_pos += 1;
        return 1; // return the number of successfully read bytes
    } else {
        return 0;
    }
}

ssize_t led_device_write(struct file* filp, char *buffer, size_t count, loff_t *f_pos) {
    // similar to FWRITE
    char *tmp;
    char led_temp_buffer;
    tmp = buffer + count - 1; // reading pos;
    copy_from_user(&led_temp_buffer, tmp, 1);
    outb(led_temp_buffer, LED_ADDRESS);
    return 1;
}

int port;

void led_device_exit(void) {
    unregister_chrdev(led_device_major, "leddevice");
    if (!port) {
        release_region(LED_ADDRESS, 1);
    }
    printk("<1> Unregistering led driver.\n");
}

int led_device_init(void) {
    printk("<1> Entering led driver.\n");
    int registerResult;
    registerResult = register_chrdev(led_device_major, "leddevice", &led_device_fops);
    if (registerResult < 0) {
        printk("<1>LED_DEVICE: cannot obtain major number %d\n", led_device_major);
        return registerResult;
    }

    port = check_region(LED_ADDRESS, 1);
    if (port) {
        printk("<1> LED_DEVICE: cannot reserve LED_ADDRESS\n");
        registerResult = port;
        led_device_exit();
        return registerResult; 
    }

    request_region(LED_ADDRESS, 1, "leddevice");

    printk("<1>Inserting leddevice module\n");
    return 0;
}

module_init(led_device_init);
module_exit(led_device_exit);
