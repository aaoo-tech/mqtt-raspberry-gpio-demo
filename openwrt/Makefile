include $(TOPDIR)/rules.mk

PKG_NAME:=aaoo_openwrt_mqtt
PKG_VERSION:=0.0.1
PKG_BUILD_DIR:= $(BUILD_DIR)/$(PKG_NAME)
	
PKG_BUILD_DEPENDS:=libmosquitto

include $(INCLUDE_DIR)/package.mk

define Package/aaoo_openwrt_mqtt
 SECTION:=base
 CATEGORY:=Utilities
 TITLE:=AAOO MQTT Demo for OpenWRT
 DEPENDS:= +libmosquitto
endef

define Package/aaoo_openwrt_mqtt/description
	AAOO MQTT Demo for OpenWRT
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/aaoo_openwrt_mqtt/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/aaoo_openwrt_mqtt $(1)/bin/
endef

$(eval $(call BuildPackage,aaoo_openwrt_mqtt,+libmosquitto))
