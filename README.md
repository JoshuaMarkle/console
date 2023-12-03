# Untitled Game Console Setup Script

This is a list of instructions to setup **Untitled Game Console**

The console is built on Arch because why not?

### Getting Started With Arch

To install Arch, will we need to do archinstall, nothing super specific and this works good enough.

```
archinstall
```

Here is the configuration used:

- Archinstall language: English
- Mirror Region: United States
- Locals:
    - Keyboard Layout: us
    - Locale Language: en_US
    - Locale Encoding: UTF-8
- Disk Layout: Use A Best-Effort Default Partition Layout
    - Filesystem: ext4
- Disk Encryption: No
- Bootloader: Grub
- Swap: True
- Hostname: console
- Root Password: None
- User Account:
    - User: user
    - Password: user
    - Sudo: True
- Profile: Xorg
- Audio: Pulseaudio
- Kernels: linux
- Additional Packages:

```
git
```

- Network Configuration: Network Manager
- Timezone: (whatever you want)
- Automatic Time Sync (NTP): True
- Optional Repositories: None
