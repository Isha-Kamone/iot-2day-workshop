# IoT-2day-workshop
Welcome to the repository for 2-day IoT workshop (21st to 22nd December 2022) 

Below is the list of required tools and specifications for this workshop and step-by-step process of how to use them.

---

### Laptop Specifications

- OS: 64-bit Windows 10 or 11 / Ubuntu 18.04 or 20.04 LTS
- Processor: i3 or later
- HDD space: 20 GB or more
- RAM: 4 GB or more



---

Following software are required to be installed:

> **NOTE**
>
> - Make sure you have Hypervisor or Virtualization enabled in your system's BIOS setup. Google search to know more about the same.
> - Also ensure the Secure Boot option in BIOS is **Disabled**.

#### 1. Virtual Box

- Open [this page](https://www.virtualbox.org/wiki/Downloads) in your browser.

- Download Virtual Box software for the OS you have pre-installed on your host machine.

- Run and Install the software. You will be greeted with a window similar to Figure 1 below.

  <center><img src="https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/iot_2day_workshop_dec_22/assets/1_vbox_startup.png" alt="virtualbox-main-empty"></center>

  <center>Figure 1: Virtual Box VM Greeting Screen</center>

- Download the Virtual Box Image (of size *~8 GB*) file named **`e-Yantra-IoT-Ubuntu20.ova`** from this [link](https://drive.google.com/file/d/1S22zLiiUgQFrd_h7EdnWI2__faaD8CX-/view?usp=sharing).

- Click on this icon ![import_icon_vbox](https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/functional_weeder/assets/task_0/vbox_sw/import_icon_vbox.png) in the window shown in Figure 1 and import the **`e-Yantra-IoT-Ubuntu20.ova`** file in Virtual Box software.

- Locate the file path where you downloaded the Virtual Box image as shown in Figure 2.

  <center><img src="https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/iot_2day_workshop_dec_22/assets/2_vbox_import_ova.png"></center>

  <center>Figure 2: Locate OVA file to import</center>

- Once imported, you will see a screen similar to Figure 3.

  <center><img src="https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/iot_2day_workshop_dec_22/assets/3_vbox_after_ova_import.png"></center>

  <center>Figure 3:  Importing OVA file in Virtual Box software</center>

- Double-click on the name **`Ubuntu_20`** in the left-pane of Figure 3 to power on the ***Ubuntu 20.04*** machine.

- On powerup, you will see screen as in Figure 4.

  <center><img src="https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/iot_2day_workshop_dec_22/assets/4_vbox_start_given_vm.png"></center>

  <center>Figure 4: Ubuntu_20 machine power up</center>

- Following are the details of Ubuntu 20.04 machine:

  - System name: **`erts`**
  - Username: **`eyantra`**
  - Password: **`eyantra123`**

- Enter the password for login and you will be greeted with screen as in Figure 5.

  <center><img src="https://raw.githubusercontent.com/kalindkaria/typora-md-assets/master/iot_2day_workshop_dec_22/assets/5_vbox_vm_booted.png"></center>

  <center>Figure 5: On login to Ubuntu_20 machine</center>

- This system has the following software installed:

  - **Arduino IDE v1.8.19**
  - **VS Code editor**
    - **Arduino extension**
    - **Espressif extension**
  - **Insomnia**
  - **Python Jupyter Notebook**

---

Great! We are now ready to use these tools for learning something new! :smile:

---
