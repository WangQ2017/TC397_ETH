############################################################################### 
# File Name  : TcpIp_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2020 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
#  1.00.00  2014-07-16  visfdn  Created
#  7.00.00  2018-04-09  visfdn  Removed (IpV4|IpV6|DhcpV4Server)_Lcfg.c
#  7.01.00  2019-02-06  vircbl  Added support of component-based SIP structure
# 12.00.00  2019-07-29  vispcn  Added IPsec source file
# 12.00.01  2020-10-23  vispcn  Removed author names from make files.
# 12.00.02  2020-11-17  vistbk  TCPIP-2359: Remove unsupported TcpIp_Ipv6_MLD
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################


###############################################################
# REGISTRY
#

include $(ROOT)\$(GLOBAL_COMP_DIR)\TcpIp\$(if $(BSW_MAKE_DIR),$(BSW_MAKE_DIR),mak)\TcpIp_cfg.mak

#e.g.: LIBRARIES_TO_BUILD      +=    $(LIB_OUPUT_PATH)\vendorx_canlib1.$(LIB_FILE_SUFFIX)
LIBRARIES_TO_BUILD      += TcpIp
TcpIp_FILES              = TcpIp$(BSW_SRC_DIR)\TcpIp.c TcpIp$(BSW_SRC_DIR)\TcpIp_Priv.c TcpIp$(BSW_SRC_DIR)\TcpIp_Tcp.c TcpIp$(BSW_SRC_DIR)\TcpIp_Udp.c TcpIp$(BSW_SRC_DIR)\TcpIp_IpSec.c

ifeq ($(TCPIP_IPV4), 1)
TcpIp_FILES             += TcpIp$(BSW_SRC_DIR)\TcpIp_IpV4.c TcpIp$(BSW_SRC_DIR)\TcpIp_IcmpV4.c TcpIp$(BSW_SRC_DIR)\TcpIp_DhcpV4.c TcpIp$(BSW_SRC_DIR)\TcpIp_Arp.c TcpIp$(BSW_SRC_DIR)\TcpIp_IpV4_Priv.c
endif

ifeq ($(TCPIP_IPV6), 1)
TcpIp_FILES             += TcpIp$(BSW_SRC_DIR)\TcpIp_IpV6.c TcpIp$(BSW_SRC_DIR)\TcpIp_IcmpV6.c TcpIp$(BSW_SRC_DIR)\TcpIp_DhcpV6.c TcpIp$(BSW_SRC_DIR)\TcpIp_Ndp.c TcpIp$(BSW_SRC_DIR)\TcpIp_IpV6_Priv.c
endif

ifeq ($(TCPIP_DHCPV4SERVER), 1)
TcpIp_FILES             += TcpIp$(BSW_SRC_DIR)\TcpIp_DhcpV4Server.c
endif

ifeq ($(GET_IMPLEMENTION_FROM), LIB)
CC_FILES_TO_BUILD       += 
else
CC_FILES_TO_BUILD       += $(TcpIp_FILES)
endif
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automaticly 
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   +=

#DEPEND_GCC_OPTS         += (not yet supported)

# e.g.:  GENERATED_SOURCE_FILES += $(GENDATA_DIR)\drv_par.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\TcpIp_Lcfg.c

COMMON_SOURCE_FILES     += 

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automaticly
# so in this clean-rule it is only necessary to define additional files which
# were not delete automaticly.
# e.g.: $(<PATH>)\can_test.c
#-------------------------------------------------------------------------------------------------
MAKE_CLEAN_RULES        +=
#MAKE_GENERATE_RULES     +=
#MAKE_COMPILER_RULES     +=
#MAKE_DEBUG_RULES        +=
#MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES          +=


###############################################################
# REQUIRED   (defined in BaseMake (global.Makefile.target.make...))
#
# SSC_ROOT		(required)
# PROJECT_ROOT	(required)
#
# LIB_OUTPUT_PATH	(optional)
# OBJ_OUTPUT_PATH	(optional)
#
# OBJ_FILE_SUFFIX	
# LIB_FILE_SUFFIX
#
###############################################################


###############################################################
# PROVIDE   this Section can be used to define own additional rules
#
# In vendorx_can_cfg.mak:
# Please configure the project file:
#CAN_CONFIG_FILE = $(PROJECT_ROOT)\source\network\can\my_can_config.cfg

#In vendorx_can_config :
#generate_can_config:
#$(SSC_ROOT)\core\com\can\tools\canconfiggen.exe -o $(CAN_CONFIG_FILE)


###############################################################
# SPECIFIC
#
# There are no rules defined for the Specific part of the 
# Rules-Makefile. Each author is free to create temporary 
# variables or to use other resources of GNU-MAKE
#
###############################################################

