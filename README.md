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
- Additional Packages: None
- Network Configuration: Network Manager
- Timezone: (whatever you want)
- Automatic Time Sync (NTP): True
- Optional Repositories: None

### Next Steps, Installing

Time to install a bunch of stuff

```
sudo pacman -S git sdl2 sdl2_ttf
```

### Getting Rid Of Grub

Go to `/etc/default/grub` and then add the following lines of code

```
GRUB_TIMEOUT=0
GRUB_HIDDEN_TIMEOUT=0
GRUB_HIDDEN_TIMEOUT_QUIET=true
```

Now, in the terminal run

```
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

### Autologin To TTY

To do this, we will use getty

Go to the location `/etc/systemd/system/getty@tty1.service.d/override.conf`. If this is not there, then make all the folders. In side the folders make an `override.conf` file to override the tty. Inside, add the following lines:

```
[Service]
ExecStart=
ExecStart=-/usr/bin/agetty --autologin user --noclear %I $TERM
```

### Installing The Console

Go back to `~` and then run:

```
git clone https://github.com/JoshuaMarkle/console
```

This will install the files needed for the actual console stuff.

At this point, everything should work. To complie the games, run:

```
cd ~/console
make
```

## References

- Fonts are from [TakWolf/retro-pixel-font](https://github.com/TakWolf/retro-pixel-font/)
