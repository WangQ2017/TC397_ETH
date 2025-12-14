############################################################################### 
# File Name  : SoAd_rules.mak 
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
# 1.00.00   2008-11-19  alr     Created
# 1.00.01   2009-10-08  alr     bugfix library support
# 1.00.02   2009-10-08  alr     file names changed
# 1.00.03   2009-11-18  alr     deleted path variables
# 1.00.04   2012-09-26  mda     changed comments and add path variables
# 1.01.00   2013-01-18  mda     added SoAd_XcpRoute.c
# 2.00.00   2013-09-27  mda     branch for ASR 4.1.1
# 3.00.00   2015-11-09  mda     added SoAd_PBcfg.c
#                               version history in <Msn>_rules.mak only
# 4.00.00   2017-11-21  mda     updated to new template
# 5.00.00   2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += SoAd$(BSW_SRC_DIR)\SoAd*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\SoAd_Lcfg.c $(GENDATA_DIR)\SoAd_PBcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += SoAd
SoAd_FILES              += SoAd$(BSW_SRC_DIR)\SoAd*.c

