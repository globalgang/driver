obj-$(CONFIG_WILC3000) += at_pwr_dev.o 

WILC3000_BT_FIRMWARE = BT_FIRMWARE=\"bt_firmware.bin\"

ccflags-y += -D$(WILC3000_BT_FIRMWARE)

TOP := $(dir $(lastword $(MAKEFILE_LIST)))
ccflags-y += -I $(TOP)/ -I $(TOP)/../wilc3000/

ccflags-y += -DPLAT_SAMA5D4

ccflags-$(CONFIG_WILC3000_SDIO) += -DATWILC_SDIO
ccflags-$(CONFIG_WILC3000_SPI) += -DATWILC_SPI
ccflags-$(CONFIG_WILC3000_HW_OOB_INTR) += -DATWILC_SDIO_IRQ_GPIO
ccflags-$(CONFIG_WILC3000_STATICALLY_ALLOCATE_MEMORY) += -DMEMORY_STATIC
ccflags-$(CONFIG_WILC3000_ENABLE_DEBUGFS) += -DATWILC_DEBUGFS

#ccflags-y += -DDOWNLOAD_BT_FW

ccflags-y += -DATWILC_ASIC_A0 -DATL_PLATFORM=ATL_LINUXKERNEL -Wno-unused-function -DUSE_WIRELESS\

at_pwr_dev-y += at_pwr_dev_main.o
at_pwr_dev-y += atwilc_debugfs.o
at_pwr_dev-y += atwilc_queue.o
at_pwr_dev-y += atwilc_sdio.o
at_pwr_dev-y += atwilc_spi.o
at_pwr_dev-y += linux_os_wrapper.o
at_pwr_dev-$(CONFIG_WILC3000_SDIO) += linux_wlan_sdio.o
at_pwr_dev-$(CONFIG_WILC3000_SPI) += linux_wlan_spi.o