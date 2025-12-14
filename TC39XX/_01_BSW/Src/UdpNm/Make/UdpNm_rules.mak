############################################################################### 
# File Name  : UdpNm_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2008-11-19  visalr  Created
# 1.00.01   2009-10-08  visalr  Bugfix library support
# 1.00.02   2009-10-08  visalr  File names changed
# 1.00.03   2012-02-21  viswmc  Bugfix SoAd_FILES --> UdpNm_FILES
# 1.01.00   2012-04-03  viswmc  Added file UdpNm_Cfg.c (Cfg5)
# 1.02.00   2013-05-07  vismha  Removed file UdpNm_Cfg.c
# 1.02.00   2013-08-08  vismha  Removed file UdpNm_PBcfg.c
# 2.00.00   2018-08-15  vispkn  Cleanup of MakeFiles
# 2.01.00   2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += UdpNm$(BSW_SRC_DIR)\UdpNm.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\UdpNm_Cfg.c $(GENDATA_DIR)\UdpNm_PBcfg.c $(GENDATA_DIR)\UdpNm_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += UdpNm
UdpNm_FILES             += UdpNm$(BSW_SRC_DIR)\UdpNm.c
