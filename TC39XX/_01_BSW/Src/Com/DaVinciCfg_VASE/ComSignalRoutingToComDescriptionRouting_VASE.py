#%VASE-API=2.0%
#######################################################################################################################
#  COPYRIGHT
#   -------------------------------------------------------------------------------------------------------------------
#   \verbatim
#   Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
#
#                 This software is copyright protected and proprietary to Vector Informatik GmbH.
#                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
#                 All other rights remain with Vector Informatik GmbH.
#   \endverbatim
#   -------------------------------------------------------------------------------------------------------------------
#   FILE DESCRIPTION
#   -----------------------------------------------------------------------------------------------------------------*/
#        \brief  VASE script to aggregate multiple single routings into Com description routings
#######################################################################################################################
#
#######################################################################################################################
#  AUTHOR IDENTITY
#  -------------------------------------------------------------------------------------------------------------------
#  Name                          Initials      Company
#  -------------------------------------------------------------------------------------------------------------------
#  Heiko Huebler                 vishho        Vector Informatik GmbH
#  Andoni Rendon Borobia         visrai        Vector Informatik GmbH
#  -------------------------------------------------------------------------------------------------------------------
#  REVISION HISTORY
#  -------------------------------------------------------------------------------------------------------------------
#  Version   Date        Author  Change Id     Description
#  -------------------------------------------------------------------------------------------------------------------
#   1.00.00  2016-01-13  vishho  -             initial version
#   1.00.01  2016-06-03  visrai  ESCAN00090127 Wrong or invalid data might be routed
#   1.01.00  2017-03-08  visrai  FEATC-805     Ignore ComSignalFilters if they are configured as always or never  
#                                              creation of error log file if an error occur during script execution
#                                              The precondition start bit position not important anymore
#                                              If one signal of one signal group does not meet the preeconditions to be
#                                              -merged, the whole signalGroup will be excluded
#   1.02.00  2017-07-17 visrai   ESCAN00095836 Signals with ByteAlignment BigEndian might not be correctly sorted 
#   1.03.00  2017-09-05 visrai   FEAT-3134     Support Signal Groups in Description Routing VASE Script, 
#                                              Support for AR4.3  
#######################################################################################################################

import clr
import os
import sys
sys.path.append("C:\Program Files (x86)\IronPython 2.7\Lib")

clr.AddReference("GenTool_CsDataServerDomAsr4.dll")

from GenTool_CsDataServerDomAsr4.Iface import ReferrableType, StorageConditionStatusEnum, EventAcceptanceStatusEnum, ByteOrderEnum, CommunicationDirectionType, ICommunicationConnector, IISignal,IISignalGroup, IISignalIPdu, IISignalIPduGroup, IISignalIPduGroupBase , IFlexrayPhysicalChannel, IARPackage, IAUTOSAR
from GenTool_CsDataServerDomAsr4.Model import * 
from System.Collections.Generic import List

from operator import itemgetter, attrgetter  # # handling of arrays (sorting)
def Find(qualifiedPathName):
    return model.Find(qualifiedPathName)

def Log(message):
    logger.Log(3, message)

def FindFirstARPackage(logFile, GatewayCollections):
    for TopLevelPackage in model.ArPackageList:
        if TopLevelPackage.ElementList.Count > 0:
            mainPackage = TopLevelPackage.Owner
            FindAutosarPackets(mainPackage,logFile, GatewayCollections)
            break

        else:
            mainPackage = TopLevelPackage.Owner
            RecursiveFunctionFindFirstARWithElementList(mainPackage,logFile, GatewayCollections)
            break
    

def RecursiveFunctionFindFirstARWithElementList(TopLevelPackage,logFile, GatewayCollections):
    for NextTopLevelPackage in TopLevelPackage.ArPackageList:
        if  NextTopLevelPackage.ElementList.Count > 0:
            FirstPacketwithElementList = NextTopLevelPackage.Owner
            FindAutosarPackets(FirstPacketwithElementList,logFile, GatewayCollections)
            break
        else:
            TopLevelPackage = NextTopLevelPackage
            RecursiveFunctionFindFirstARWithElementList(TopLevelPackage,logFile, GatewayCollections)


# ##30/11/2015 Recursive Function detects if an autosar element contains subautosar containers
def recursiveFunctionsubpackages(TopLevelsubPackage,logFile, GatewayCollections):
    if hasattr(TopLevelsubPackage, "ArPackageList"):
        if TopLevelsubPackage.ArPackageList.Count > 0:
            for PackagewithElementList in TopLevelsubPackage.ArPackageList:
                if  hasattr(PackagewithElementList, "ElementList"):
                    FirstPacketwithElementList = PackagewithElementList
                    return FirstPacketwithElementList
                    break
                else:
                    TopLevelsubPackage = NextTopLevelPackage
                    recursiveFunctionsubpackages(TopLevelsubPackage,logFile, GatewayCollections)
                    RecursiveFunctionFindFirstARWithElementList(PackagewithElementList, logFile, GatewayCollections)
        else:
            return TopLevelsubPackage
    else:
        return TopLevelsubPackage


#----------------------------------------------------------------------------------------------------------------
#-----------------------------------FindAutosar------------------------------------------------------------------
def FindAutosarPackets(mainPackage,logFile, GatewayCollections):

    iSignalMappingCollection = set()    
    iSignalMappingCounter = 0
    GatewayCounter = 0

    ISignalIPduRxCollectorArray = []
    RxPropertiesCollector = []
    RxPropertiesCollectorIndex = 0
    FlagRxCollectorIndex = False
    RxTxPropertiesCollector = []
    TxPropertiesCollector = []
    ISignalIPduTxCollectorArray = []
    TxPropertiesCollectorIndex = 0
    iSignalIPduCollection = set()
    DiscardISignalGroupsFromCollection = []

    for ARPackage in mainPackage.ArPackageList:
        if hasattr(ARPackage, "ArPackageList") and hasattr(ARPackage, "ElementList"):
            if ARPackage.ElementList.Count > 0:
                Package1 = ARPackage

                for Package in Package1.ElementList:

                    if type(Package) is VGateway:
                        GatewayCounter += 1
                        GatewayCollections.Add(Package)

                        # #ISignalMapping
                        ss = Package.SignalMappingList
                        for ISignalMapping in Package.SignalMappingList:

                            if type(ISignalMapping) is VISignalMapping:
                                
                                iSignalMappingCounter += 1
                                iSignalMapping = ISignalMapping
                                iSignalMappingCollection.add(ISignalMapping)
                                Start_Find_elements_Source_and_TargetSignal(ISignalMapping, ISignalIPduRxCollectorArray, RxTxPropertiesCollector,logFile)

    if iSignalMappingCounter > 0:
        Create_AdminPackage(GatewayCollections)
        logFile.write("\n \n \n \n ")         
        logFile.write("\n ***************************************************************************************************************************************************************************************") 
        logFile.write("\n ***************************************************************************************************************************************************************************************") 
        logFile.write("\n ***************************************************************************************************************************************************************************************") 
        logFile.write("\n Analysing possible Gaps between bit positions and creating new Description Routings......") 
        
         
        AnalyseSignalGroupsCollectedInformation(ISignalIPduRxCollectorArray, GatewayCollections,DiscardISignalGroupsFromCollection, logFile)
        
        DiscardNotValidISignalGroupsFromCollector(ISignalIPduRxCollectorArray,DiscardISignalGroupsFromCollection, logFile)

        CheckPreconditionsForExistentCollection(ISignalIPduRxCollectorArray,GatewayCollections,logFile)

        Create_ComDescription_Routings(ISignalIPduRxCollectorArray, GatewayCollections,logFile)

    else:
        print("no ISignalMappings found")

    return mainPackage

# #Create AdminPackage in Gateway
def Create_AdminPackage(GatewayCollections):
  for Gateway in GatewayCollections:
      if Gateway.AdminDataSpecified == False:  # ##suport for one gateway!
         Gateway.AdminDataSpecified = True



def CheckPreconditionsForExistentCollection(ISignalIPduRxCollectorArray, GatewayCollections,logFile):
    emptyPdusToDelete = []
    for collectedSignalMappingInfo in ISignalIPduRxCollectorArray:    
        listToDelete = []
        for element in range(len(collectedSignalMappingInfo)):
            if element > 0:
               check_precondition = check_preconditions(collectedSignalMappingInfo[element][8], collectedSignalMappingInfo[element][9])               
               if check_precondition is None:  # does not meet the preeconditions
                  collectedSignalMappingInfo[element].append("delete")
                  listToDelete.Add(collectedSignalMappingInfo[element])
                  logFile.write("\n") 
                  logFile.write("\n Attention ----> the Signal Mapping with the source {0} and the target {1} does NOT meet the preconditions to be merged".format(collectedSignalMappingInfo[element][16].SourceSignal.Value, collectedSignalMappingInfo[element][16].TargetSignal.Value))
                  logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
               else:
                  logFile.write("\n") 
                  logFile.write("\n the Signal Mapping with the source {0} and the target {1} meets the preconditions to be merged".format(collectedSignalMappingInfo[element][16].SourceSignal.Value, collectedSignalMappingInfo[element][16].TargetSignal.Value))
                  logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
    #else:



                  
        for delete in listToDelete:                                  
            if delete.Count == 26: 
               index = collectedSignalMappingInfo.index(delete)                   
               collectedSignalMappingInfo.Remove(collectedSignalMappingInfo[index])
               if collectedSignalMappingInfo.Count == 1:
                  emptyPdusToDelete.Add(collectedSignalMappingInfo)

    for collectedPdusWithoutSignalMappings in emptyPdusToDelete:            
        if(collectedPdusWithoutSignalMappings.Count == 1):
           ISignalIPduRxCollectorArray.Remove(collectedPdusWithoutSignalMappings)    #delete from the collector 
        
           

def AnalyseSignalGroupsCollectedInformation(ISignalIPduRxCollectorArray, GatewayCollections,DiscardISignalGroupsFromCollection, logFile):
    
    

    for CollectedPduSignalMapping in ISignalIPduRxCollectorArray: 

        SignalGroupsMappedRx = []
        SignalGroupsMappedTx = []
        CounterElementsWithSignalGroupRefRx = 0
        CounterElementsWithSignalGroupRefTx = 0
        index = 0

        for element in range(len(CollectedPduSignalMapping)):
            GroupAlreadySaved = False
            if(element > 0):
               
              if type(CollectedPduSignalMapping[element][23]) is VISignalGroup:
                          
                 if(SignalGroupsMappedTx.Count >0):
                    for mappedSignalGroup in SignalGroupsMappedTx:
                        if(mappedSignalGroup[0] == (CollectedPduSignalMapping[element][23])):
                           CounterElementsWithSignalGroupRefTx +=1
                           SignalGroupsMappedTx[index].append(CollectedPduSignalMapping[element])
                           GroupAlreadySaved = True
                       
                 elif(SignalGroupsMappedTx.Count == 0) or GroupAlreadySaved == False:                   
                      SignalGroupsMappedTx.append([])
                      CounterElementsWithSignalGroupRefTx += 1
                      SignalGroupsMappedTx[index].append(CollectedPduSignalMapping[element][23])
                      SignalGroupsMappedTx[index].append(CollectedPduSignalMapping[element])

                
        
        DiscardGroups = False
        for collectedSignalGroups in SignalGroupsMappedTx:
            signalsDifferentSignalGroups = False
            SignalGroupRx = None
            for indexTx in range(len(collectedSignalGroups)):
                if indexTx == 1:
                    SignalGroupRx = collectedSignalGroups[indexTx][21]                    
                elif indexTx >1:
                    if not SignalGroupRx == collectedSignalGroups[indexTx][21]:
                       signalsDifferentSignalGroups = True
                       DiscardGroups = True
                       break; 

                    if(signalsDifferentSignalGroups == False):                
                       #check preconditions
                       check_precondition = check_preconditions(collectedSignalGroups[indexTx][8], collectedSignalGroups[indexTx][9])
                       if not check_precondition == 0:  # match!
                          #discard both signal Groups from the Collection
                          ###############################################################################                           
                          DiscardISignalGroupsFromCollection.Add(collectedSignalGroups)
                          DiscardGroups = True
                          break;
                          ##else ---> the signal Groups can be considered to be candidates to create ComDescriptionRoutings
                   
                   
                    elif(signalsDifferentSignalGroups == True):
                         #discard both signal Groups from the Collection
                         ###############################################################################             
                         ## it means the RX signal belongs to another SignalGroup -----> discard both of them                         
                         DiscardISignalGroupsFromCollection.Add(collectedSignalGroups)
                         DiscardGroups = True
                         break;
                          
            if(DiscardGroups == True):
              break


def DiscardNotValidISignalGroupsFromCollector(ISignalIPduRxCollectorArray,DiscardISignalGroupsFromCollection, logFile):
    for ISignalsToDiscard in DiscardISignalGroupsFromCollection:
        logFile.write("\n")
        logFile.write("\n -------------------------------------------------------------------------------------")
        logFile.write("\n for the ISignalGroup:" + ISignalsToDiscard[0].AsrPath)
        logFile.write("\n  " + str(ISignalsToDiscard.Count -1) + " signals dont satisfy the preconditions to be merged, therefore the whole signalGroup will be discarded")                            
        #find ISignalIPdu
        for collectedPdus in ISignalIPduRxCollectorArray:

            if collectedPdus[0].AsrPath == ISignalsToDiscard[1][0].AsrPath:

               for savedElement in range(len(ISignalsToDiscard)):
                if(savedElement > 0):
                    
                    index = collectedPdus.index(ISignalsToDiscard[savedElement])
                    collectedPdus[index].append("delete")
                    collectedPdus.Remove(collectedPdus[index])
                              

               

        for collectedPdus in ISignalIPduRxCollectorArray:            
            if(collectedPdus.Count == 1):
               ISignalIPduRxCollectorArray.Remove(collectedPdus)
            
       

def Start_Find_elements_Source_and_TargetSignal(ISignalMapping, ISignalIPduRxCollectorArray, RxTxPropertiesCollector, logFile):
    
    ISignalIPduRx  = None
    ISignalIPduTx  = None
    # #ISignalTriggering in sourceSignal
    ############################################################################################################################################################
    for ISignalTriggeringRx in ISignalMapping.SourceSignal.ObjectList:
    
        if ISignalTriggeringRx.ISignalSpecified == True:
            # ISignal Path Rx Source
            ISignalLocationRx = str.format(ISignalTriggeringRx.ISignal.Value)
            ARISignalPackageListRx = model.Find(ISignalLocationRx)

            moreThanOneISignalToIPduMappingSource = 0
            ISignalToIPduMappingRx = None
            
        
            ###Update: if an ISignal is being referenced by several ISignalToIpduMappings the script has to find out which ISignalIPdu will be sent
            for ISignalRx in ARISignalPackageListRx:            
                for ISignalrefsRx in ISignalRx.ReferencedFromList:
                    if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                        moreThanOneISignalToIPduMappingSource = moreThanOneISignalToIPduMappingSource + 1 

            if moreThanOneISignalToIPduMappingSource == 1:
               for ISignalRx in ARISignalPackageListRx:            
                   for ISignalrefsRx in ISignalRx.ReferencedFromList:
                
                       if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                        ISignalToIPduMappingRx = ISignalrefsRx.Owner
                        ISignalIPduRx = ISignalToIPduMappingRx.Owner

                        # #Find IPduref
                        for IPdurefRx in ISignalIPduRx.ReferencedFromList:
                            if type(IPdurefRx.Owner) is VPduTriggering and type(IPdurefRx) is VPdu_Ref:
                               IPduTriggeringrefRx = IPdurefRx.Owner

            elif moreThanOneISignalToIPduMappingSource > 1:
                ISignalIPduRx = None
                for findPduTriggering in ISignalTriggeringRx.ReferencedFromList:
                    if type(findPduTriggering.Owner.Owner is VPduTriggering):
                        IPduTriggeringrefRx = findPduTriggering.Owner.Owner
                        ISignalIPduRx = model.Find(IPduTriggeringrefRx.IPdu.Value)
                        break

                for ISignalrefsRx in ISignalRx.ReferencedFromList:
                
                    if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                       ISignalToIPduMappingRxToCompare = ISignalrefsRx.Owner
                       if(ISignalToIPduMappingRxToCompare.Owner.AsrPath == ISignalIPduRx[0].AsrPath):
                          ISignalToIPduMappingRx = ISignalrefsRx.Owner
                          ISignalIPduRx = ISignalToIPduMappingRx.Owner
                          break
            
    ############################################################################################################################################################




    # #ISignalTriggering in targetSignal
    ############################################################################################################################################################
    for ISignalTriggeringTx in ISignalMapping.TargetSignal.ObjectList:
        
        if ISignalTriggeringTx.ISignalSpecified == True:
            # ISignal Path Tx Target
            ISignalLocationTx = str.format(ISignalTriggeringTx.ISignal.Value)
            ARISignalPackageListTx = model.Find(ISignalLocationTx)

            moreThanOneISignalToIPduMappingTarget = 0
            ISignalToIPduMappingTx = None
         
        
            ###Update: if an ISignal is being referenced by several ISignalToIpduMappings the script has to find out which ISignalIPdu will be sent
                    ###Update: if an ISignal is being referenced by several ISignalToIpduMappings the script has to find out which ISignalIPdu will be sent
            for ISignalTx in ARISignalPackageListTx:            
                for ISignalrefsTx in ISignalTx.ReferencedFromList:
                    if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                        moreThanOneISignalToIPduMappingTarget = moreThanOneISignalToIPduMappingTarget + 1 

            if moreThanOneISignalToIPduMappingTarget == 1:

               for ISignalTx in ARISignalPackageListTx:
                   for ISignalrefsTx in ISignalTx.ReferencedFromList:
                       if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                          ISignalToIPduMappingTx = ISignalrefsTx.Owner
                          # ISignalIPdu
                          ISignalIPduTx = ISignalToIPduMappingTx.Owner
 
                          # #Find IPduref
                          for IPdurefTx in ISignalIPduTx.ReferencedFromList:
                              if type(IPdurefTx.Owner) is VPduTriggering and type(IPdurefTx) is VPdu_Ref:
                                 IPduTriggeringrefTx = IPdurefTx.Owner

            elif moreThanOneISignalToIPduMappingTarget > 1:
                ISignalIPduTx = None
                for findPduTriggering in ISignalTriggeringTx.ReferencedFromList:
                    if type(findPduTriggering.Owner.Owner is VPduTriggering):
                        IPduTriggeringrefTx = findPduTriggering.Owner.Owner
                        ISignalIPduTx = model.Find(IPduTriggeringrefTx.IPdu.Value)
                        break

                for ISignalrefsTx in ISignalTx.ReferencedFromList:
                
                    if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                       ISignalToIPduMappingTxToCompare = ISignalrefsTx.Owner
                       if(ISignalToIPduMappingTxToCompare.Owner.AsrPath == ISignalIPduTx[0].AsrPath):
                          ISignalToIPduMappingTx = ISignalrefsTx.Owner
                          ISignalIPduTx = ISignalToIPduMappingTx.Owner
                          break

    ############################################################################################################################################################

    #check_precondition = check_preconditions(ISignalToIPduMappingRx, ISignalToIPduMappingTx)
    #if not check_precondition is None:  # match!
            ###################SAVE ISignalIPDU Tx
            # find index
    
    if  ISignalIPduTx is not None and ISignalIPduRx is not None:
        if RxTxPropertiesCollector.Count == 0:
            RxTxPropertiesCollectorIndex = 0
        else:
            RxTxPropertiesCollectorIndex = RxTxPropertiesCollector.Count
        RxTxPropertiesCollector.append([])
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalIPduRx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalIPduTx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping.SourceSignal.Value)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping.TargetSignal.Value)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalRx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalRx.Length.SignedValue)  # #length
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTx.Length.SignedValue)  # #length
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx)

        if format(ISignalToIPduMappingRx.PackingByteOrder) == "eMostSignificantByteLast":
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Intel")
        else:
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Motorola")

        if format(ISignalToIPduMappingTx.PackingByteOrder) == "eMostSignificantByteLast":
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Intel")
        else:
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Motorola")

        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTriggeringRx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTriggeringTx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(IPduTriggeringrefRx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(IPduTriggeringrefTx)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.StartPosition.SignedValue)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.TransferProperty)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.StartPosition.SignedValue)
        RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.TransferProperty)
        
        
        #find out whether the signal Rx belongs to a signal Group
        ################################################################################################################
        referencedElementsISignalRx =  ISignalRx.ReferencedFromList
        referencedElementsISignalTx = ISignalTx.ReferencedFromList

        rxGroupSignal = False
        txGroupSignal = False

        rxISignalGroup = None
        txISignalGroup = None

        for referencedElementRx in referencedElementsISignalRx:
            if(type(referencedElementRx.Owner) is VISignalGroup):
               
                rxGroupSignal = True
                rxISignalGroup = referencedElementRx.Owner
                break
        
           
        #find out whether the signal Rx belongs to a signal Group        
        for referencedElementTx in referencedElementsISignalTx:
            if(type(referencedElementTx.Owner) is VISignalGroup):
                txGroupSignal = True
                txISignalGroup = referencedElementTx.Owner
                break
        ################################################################################################################


        if(rxGroupSignal == True):
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(rxISignalGroup)
         
        
            #Update indication bit position Rx ---> if the isignalToIpduMapping of the ISignalGroup has this parameter then substitute it
            for referencedElementsSignalGroupRx in rxISignalGroup.ReferencedFromList:
                if isinstance(referencedElementsSignalGroupRx.Owner,VISignalToIPduMapping):                
                   ISignalToIPduMappingISignalGroupRx = referencedElementsSignalGroupRx.Owner
                   if(ISignalToIPduMappingISignalGroupRx.UpdateIndicationBitPositionSpecified == True):
                      RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingISignalGroupRx.UpdateIndicationBitPosition)
                   elif(ISignalToIPduMappingRx.UpdateIndicationBitPositionSpecified == True):
                      RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.UpdateIndicationBitPosition)
                   else:
                      RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("RxNoUpdateBit")

        else:
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("RxnoSignalGroup")                  

            #UpdateIndicationBitPosition 
            if(ISignalToIPduMappingRx.UpdateIndicationBitPositionSpecified == True):
               RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.UpdateIndicationBitPosition)
            else:
               RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("RxNoUpdateBit")



        if(txGroupSignal == True):
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(txISignalGroup)
            #Update indication bit position Rx ---> if the isignalToIpduMapping of the ISignalGroup has this parameter then substitute it
            for referencedElementsSignalGroupTx in txISignalGroup.ReferencedFromList:
                if isinstance(referencedElementsSignalGroupTx.Owner,VISignalToIPduMapping):
                   ISignalToIPduMappingISignalGroupTx = referencedElementsSignalGroupTx.Owner
                   if(ISignalToIPduMappingISignalGroupTx.UpdateIndicationBitPositionSpecified == True):
                      RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingISignalGroupTx.UpdateIndicationBitPosition)
                   elif(ISignalToIPduMappingTx.UpdateIndicationBitPositionSpecified == True):
                       RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.UpdateIndicationBitPosition)
                   else:
                      RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("TxNoUpdateBit")

        else:
            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("TxnoSignalGroup")
    
            #Update indication bit position Rx
            if(ISignalToIPduMappingTx.UpdateIndicationBitPositionSpecified == True):
               RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.UpdateIndicationBitPosition)
            else:
               RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("TxNoUpdateBit")
        


        saveISignalIPduRxCollection(ISignalIPduRx , ISignalIPduRxCollectorArray, RxTxPropertiesCollector[RxTxPropertiesCollectorIndex])

    else:
        print "ISignalGroups Routing found"
        AnalyseSignalGroupMappings(ISignalMapping, ISignalIPduRxCollectorArray, RxTxPropertiesCollector, logFile)




def AnalyseSignalGroupMappings(ISignalMapping, ISignalIPduRxCollectorArray, RxTxPropertiesCollector, logFile):
    ISignalIPduRx  = None
    ISignalIPduTx  = None
    ISignalGroupInTX = None
    ISignalGroupInRX = None
    
    RxTxPairs = []
    # #ISignalTriggering in sourceSignal
    ############################################################################################################################################################
    for ISignalTriggeringRx in ISignalMapping.SourceSignal.ObjectList:
    
        if ISignalTriggeringRx.ISignalGroupSpecified == True:
            # ISignal Path Rx Source
            ISignalLocationRx = str.format(ISignalTriggeringRx.ISignalGroup.Value)
            ARISignalPackageListRx = model.Find(ISignalLocationRx)

            moreThanOneISignalToIPduMappingSource = 0
            ISignalToIPduMappingGroupRx = None
            
            ISignalGroupInRX = ARISignalPackageListRx[0]
            ###Update: if an ISignalGroup is being referenced by several ISignalToIpduMappings the script has to find out which ISignalIPdu will be sent/receive
            for ISignalGroupRx in ARISignalPackageListRx:            
                for ISignalrefsRx in ISignalGroupRx.ReferencedFromList:
                    if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                        moreThanOneISignalToIPduMappingSource = moreThanOneISignalToIPduMappingSource + 1 

            if moreThanOneISignalToIPduMappingSource == 1:
               for ISignalGroupRx in ARISignalPackageListRx:            
                   for ISignalrefsRx in ISignalGroupRx.ReferencedFromList:
                
                       if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                          ISignalToIPduMappingGroupRx = ISignalrefsRx.Owner
                          ISignalIPduRx = ISignalToIPduMappingGroupRx.Owner

                          # #Find IPduref
                          for IPdurefRx in ISignalIPduRx.ReferencedFromList:
                              if type(IPdurefRx.Owner) is VPduTriggering and type(IPdurefRx) is VPdu_Ref:
                                 IPduTriggeringrefRx = IPdurefRx.Owner
                                 break


            elif moreThanOneISignalToIPduMappingSource > 1:
                ISignalIPduRx = None
                for findPduTriggering in ISignalTriggeringRx.ReferencedFromList:
                    if type(findPduTriggering.Owner.Owner is VPduTriggering):

                        #find PduTriggering and ISignalIPdu
                        IPduTriggeringrefRx = findPduTriggering.Owner.Owner
                        ISignalIPduRx = model.Find(IPduTriggeringrefRx.IPdu.Value)
                        break

                
                for ISignalrefsRx in ISignalGroupRx.ReferencedFromList:

                    #find ISignalToIPduMapping of ISignal Rx
                    if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                       ISignalToIPduMappingRxToCompare = ISignalrefsRx.Owner
                       if(ISignalToIPduMappingRxToCompare.Owner.AsrPath == ISignalIPduRx[0].AsrPath):
                          ISignalToIPduMappingGroupRx = ISignalrefsRx.Owner
                          ISignalIPduRx = ISignalToIPduMappingGroupRx.Owner
                          break

                                

            
    ############################################################################################################################################################



    # #ISignalTriggering in targetSignal
    ############################################################################################################################################################
    for ISignalTriggeringTx in ISignalMapping.TargetSignal.ObjectList:
            
        if ISignalTriggeringTx.ISignalGroupSpecified == True:
            #ISignal Path Tx Target
            ISignalLocationTx = str.format(ISignalTriggeringTx.ISignalGroup.Value)
            ARISignalPackageListTx = model.Find(ISignalLocationTx)

            moreThanOneISignalToIPduMappingTarget = 0
            ISignalToIPduMappingGroupTx = None
            ISignalGroupInTX = ARISignalPackageListTx[0]
        
            ###Update: if an ISignalGroup is being referenced by several ISignalToIpduMappings the script has to find out which ISignalIPdu will be sent/receive
            
            for ISignalGroupTx in ARISignalPackageListTx:            
                for ISignalrefsTx in ISignalGroupTx.ReferencedFromList:
                    if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                        moreThanOneISignalToIPduMappingTarget = moreThanOneISignalToIPduMappingTarget + 1 

            if moreThanOneISignalToIPduMappingTarget == 1:

               for ISignalGroupTx in ARISignalPackageListTx:
                   for ISignalrefsTx in ISignalGroupTx.ReferencedFromList:
                       if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                          ISignalToIPduMappingGroupTx = ISignalrefsTx.Owner
                          # ISignalIPdu
                          ISignalIPduTx = ISignalToIPduMappingGroupTx.Owner
 
                          # #Find IPduref
                          for IPdurefTx in ISignalIPduTx.ReferencedFromList:
                              if type(IPdurefTx.Owner) is VPduTriggering and type(IPdurefTx) is VPdu_Ref:
                                 IPduTriggeringrefTx = IPdurefTx.Owner
                                 break



            elif moreThanOneISignalToIPduMappingTarget > 1:
                ISignalIPduTx = None
                for findPduTriggering in ISignalTriggeringTx.ReferencedFromList:
                    if type(findPduTriggering.Owner.Owner is VPduTriggering):
                        
                        #find PduTriggering and ISignalIPdu
                        IPduTriggeringrefTx = findPduTriggering.Owner.Owner
                        ISignalIPduTx = model.Find(IPduTriggeringrefTx.IPdu.Value)
                        break

                for ISignalrefsTx in ISignalGroupTx.ReferencedFromList:
                
                    if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                       ISignalToIPduMappingTxToCompare = ISignalrefsTx.Owner
                       if(ISignalToIPduMappingTxToCompare.Owner.AsrPath == ISignalIPduTx[0].AsrPath):
                          ISignalToIPduMappingGroupTx = ISignalrefsTx.Owner
                          ISignalIPduTx = ISignalToIPduMappingGroupTx.Owner
                          break

    ############################################################################################################################################################


    ###################SAVE ISignalIPDU Tx                
    if  ISignalIPduTx is not None and ISignalIPduRx is not None:
        
        for iSignalMemberOfISignalGroupTx in ISignalGroupInTX.ISignalList: 

            if RxTxPropertiesCollector.Count == 0:
                RxTxPropertiesCollectorIndex = 0
            else:
                RxTxPropertiesCollectorIndex = RxTxPropertiesCollector.Count


            #find ISignalTx
            
            iSignalTxToMatchRef = str.format(iSignalMemberOfISignalGroupTx.Value)
            findISignalTx = model.Find(iSignalTxToMatchRef)
            if findISignalTx.Count >0:
               isignalToMatchTx = findISignalTx[0]

               #find ShortName of SignalTx in Rx
               for iSignalMemberOfISignalGroupRx in ISignalGroupInRX.ISignalList: 
                   iSignalRxToMatchRef = str.format(iSignalMemberOfISignalGroupRx.Value)
                   findISignalRx = model.Find(iSignalRxToMatchRef)
                   if findISignalRx.Count >0:
                      isignalToMatchRx = findISignalRx[0]

                      if isignalToMatchTx.ShortName == isignalToMatchRx.ShortName:                         
                         
                         #find ISignalToIPduMapping Tx
                         for ISignalrefsTx in isignalToMatchTx.ReferencedFromList:
                
                             if type(ISignalrefsTx.Owner) is VISignalToIPduMapping:
                                ISignalToIPduMappingTxToCompare = ISignalrefsTx.Owner
                                if(ISignalToIPduMappingTxToCompare.Owner.AsrPath == ISignalIPduTx.AsrPath):
                                   ISignalToIPduMappingTx = ISignalrefsTx.Owner
                                   ISignalIPduTx = ISignalToIPduMappingTx.Owner
                                   


                                    #find isignalTriggering of ISignal Tx
                                   for ISignaltx in isignalToMatchTx.ReferencedFromList:                
                                       if type(ISignaltx.Owner) is VISignalTriggering:
                                          ISignalTriggeringTxISignal = ISignaltx.Owner                                                    
                                          break
                                

                         #find ISignalToIPduMapping Rx
                         for ISignalrefsRx in isignalToMatchRx.ReferencedFromList:
                
                             if type(ISignalrefsRx.Owner) is VISignalToIPduMapping:
                                ISignalToIPduMappingRxToCompare = ISignalrefsRx.Owner
                                if(ISignalToIPduMappingRxToCompare.Owner.AsrPath == ISignalIPduRx.AsrPath):
                                   ISignalToIPduMappingRx = ISignalrefsRx.Owner
                                   ISignalIPduRx = ISignalToIPduMappingRx.Owner
                                   
                               
                                   #find isignalTriggering of ISignal Rx
                                   for ISignalRx in isignalToMatchRx.ReferencedFromList:                
                                       if type(ISignalRx.Owner) is VISignalTriggering:
                                          ISignalTriggeringRxISignal = ISignalRx.Owner                                                    
                                          break

                         RxTxPropertiesCollector.append([])
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalIPduRx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalIPduTx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping.SourceSignal.Value)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping.TargetSignal.Value)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(isignalToMatchRx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(isignalToMatchRx.Length.SignedValue)  # #length
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(isignalToMatchTx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(isignalToMatchTx.Length.SignedValue)  # #length
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx)

                         if format(ISignalToIPduMappingRx.PackingByteOrder) == "eMostSignificantByteLast":
                            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Intel")
                         else:
                            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Motorola")

                         if format(ISignalToIPduMappingTx.PackingByteOrder) == "eMostSignificantByteLast":
                            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Intel")
                         else:
                            RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("Motorola")

                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTriggeringRxISignal)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalTriggeringTxISignal)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(IPduTriggeringrefRx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(IPduTriggeringrefTx)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalMapping)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.StartPosition.SignedValue)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.TransferProperty)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.StartPosition.SignedValue)
                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.TransferProperty)
        
        

                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalGroupInRX)                 
                         #Update indication bit position Rx ---> if the isignalToIpduMapping of the ISignalGroup has this parameter then substitute it
                         for referencedElementsSignalGroupRx in ISignalGroupInRX.ReferencedFromList:
                             if isinstance(referencedElementsSignalGroupRx.Owner,VISignalToIPduMapping):                
                                ISignalToIPduMappingISignalGroupRx = referencedElementsSignalGroupRx.Owner
                                if(ISignalToIPduMappingISignalGroupRx.UpdateIndicationBitPositionSpecified == True):
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingISignalGroupRx.UpdateIndicationBitPosition)
                                elif(ISignalToIPduMappingRx.UpdateIndicationBitPositionSpecified == True):
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingRx.UpdateIndicationBitPosition)
                                else:
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("RxNoUpdateBit")


                         RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalGroupInTX)
                         #Update indication bit position Rx ---> if the isignalToIpduMapping of the ISignalGroup has this parameter then substitute it
                         for referencedElementsSignalGroupTx in ISignalGroupInTX.ReferencedFromList:
                             if isinstance(referencedElementsSignalGroupTx.Owner,VISignalToIPduMapping):
                                ISignalToIPduMappingISignalGroupTx = referencedElementsSignalGroupTx.Owner
                                if(ISignalToIPduMappingISignalGroupTx.UpdateIndicationBitPositionSpecified == True):
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingISignalGroupTx.UpdateIndicationBitPosition)
                                elif(ISignalToIPduMappingTx.UpdateIndicationBitPositionSpecified == True):
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append(ISignalToIPduMappingTx.UpdateIndicationBitPosition)
                                else:
                                    RxTxPropertiesCollector[RxTxPropertiesCollectorIndex].append("TxNoUpdateBit")

        
                         
                         saveISignalIPduRxCollection(ISignalIPduRx , ISignalIPduRxCollectorArray, RxTxPropertiesCollector[RxTxPropertiesCollectorIndex])
                         break;
        
    else:
        print "error while analysing a Group SignalMapping"
        





def Create_ComDescription_Routings(ISignalIPduRxCollectorArray, GatewayCollections,logFile):
    

    #RX
    #*******************************************************************************************************************************************
    Index = 0
    CounterRxElements = 0
    SortPositionPdumappingsRx = []
    SortPositionPdumappingsRxIndex = 0
    counter = 0
    # Sort the array according to the bitposition
    for SortISignalIPduTxRx in ISignalIPduRxCollectorArray:       

        CounterRxElements = SortISignalIPduTxRx.Count

        # ##order TxRx information
        if (format(SortISignalIPduTxRx[1][10])) == "Intel":
            for bsort in range(len(SortISignalIPduTxRx) - 1, 0, -1):
               for i in range(bsort):
                   if  i > 0 :
                       if SortISignalIPduTxRx[i][17] > SortISignalIPduTxRx[i + 1][17]:
                          temp = SortISignalIPduTxRx[i]
                          SortISignalIPduTxRx[i] = SortISignalIPduTxRx[i + 1]
                          SortISignalIPduTxRx[i + 1] = temp

        arraybitpositions = []
        MotorolaCounter = 0
        IntelCounter = 0
        bitsalreadyOccupied = 0
        for j in range(CounterRxElements):
            if j == 0:

                # create frame to store the positions
                frame = []
                frame.append([])

            if j > 0:

                Vbitlength = int(SortISignalIPduTxRx[j][5])
                Vtype = format(SortISignalIPduTxRx[j][10])
                VstartPosition = int(SortISignalIPduTxRx[j][17])

                arraybitpositions.append([])
                arraybitpositions[j - 1].append(SortISignalIPduTxRx[j][8])


                if (format(SortISignalIPduTxRx[j][10])) == "Intel":
                    IntelCounter += 1

                    IntelbitCount = VstartPosition + Vbitlength - 1  # #positions to be occupied

                    IntelNextpositiontostart = IntelbitCount + 1  # startposition

                    # #save already occupied slots
                    positionCopy = IntelNextpositiontostart - Vbitlength  # #
                    while positionCopy < IntelNextpositiontostart:  # VStartPosition
                            frame[0].append(positionCopy)
                            arraybitpositions[j - 1].append(positionCopy)
                            positionCopy += 1


                # ##MOTOROLA

                elif (format(SortISignalIPduTxRx[j][10])) == "Motorola":
                      MotorolaCounter += 1
                      bitposition = VstartPosition
                      freeslots = (VstartPosition % 8) + 1                  
                      if(Vbitlength <= freeslots):
                         bitsToFill = Vbitlength
                         while(bitsToFill >0):
                              arraybitpositions[j-1].Add(bitposition)
                              bitsToFill -= 1
                              bitposition -=1
                     
                      elif(Vbitlength > freeslots):
                          bitsNextBlock = Vbitlength - freeslots
                          bitsToFill = Vbitlength - bitsNextBlock


                          if bitsNextBlock <= 8 :
                              whitespacesNextBlock = 8 - bitsNextBlock

                              while(bitsToFill > 0):
                                  arraybitpositions[j-1].Add(bitposition)
                                  bitsToFill -= 1
                                  freeslots -= 1
                                  bitposition -=1

                              if(bitposition <0):
                                  bitposition = 0 
                                  bitposition +=15
                              else:
                                  bitposition +=16
                              

                              startNextBlock = bitposition
                          
                              while(bitsNextBlock >0):
                                   arraybitpositions[j-1].Add(startNextBlock)
                                   startNextBlock -=1
                                   bitsNextBlock -=1
                        
                          elif(bitsNextBlock > 8):
                               whitespacesNextBlock = bitsNextBlock
                               bitsToFill = Vbitlength - bitsNextBlock

                               while(bitsToFill >0):
                                    arraybitpositions[j-1].Add(bitposition)
                                    bitsToFill -= 1                                    

                                    if bitposition > 0:     
                                       bitposition -=1
                                    
                                       
                                    
                               firstCycle = True  
                               mod = (bitposition % 8)
                               if mod == 0:                                                                    
                                  bitposition += 15

                               else:
                                   bitposition += 16 

                               while(bitsNextBlock >0):
                                    if(firstCycle == False):
                                       mod = (bitposition % 8) 
                                       if(mod == 0):                                                                                                                  
                                          arraybitpositions[j-1].Add(bitposition)                                    
                                          bitsNextBlock -=1
                                          bitposition += 15
                                       else:
                                          arraybitpositions[j-1].Add(bitposition)                                    
                                          bitsNextBlock -=1
                                          bitposition -=1
                                          

                                    else:
                                        arraybitpositions[j-1].Add(bitposition)                                    
                                        bitsNextBlock -=1
                                        bitposition -=1
                                        firstCycle = False

    #*******************************************************************************************************************************************

     
        create_AdminData(IntelCounter, MotorolaCounter, arraybitpositions, SortISignalIPduTxRx, GatewayCollections, frame, logFile )



def orderBigEndian(positionCollector, numberToFind, start, incrementor, maxValueToAnalyse):
    found = False
    currentValue = start 
    
    for i in xrange(start,len(positionCollector)):
         for j in xrange(1,len(positionCollector[i][1])):

             if positionCollector[i][1][j] == numberToFind:
                found = True
                if i >start:
                   shiftElements = i
                   while shiftElements > start:  
                         temp =  positionCollector[shiftElements]
                         positionCollector[shiftElements] = positionCollector[shiftElements - 1]
                         positionCollector[shiftElements - 1] = temp
                         shiftElements -=1

                   k = positionCollector[shiftElements][1][positionCollector[shiftElements][1].Count -1] 
                   mod0 = positionCollector[shiftElements][1][positionCollector[shiftElements][1].Count -1]   % 8
                   if mod0 > 0:   
                      numberToFind = positionCollector[shiftElements][1][positionCollector[shiftElements][1].Count -1]  -1
                      start = start +1
                   else:
                      numberToFind = positionCollector[shiftElements][1][positionCollector[shiftElements][1].Count -1]  +15
                      start = start +1

                else:
                    k = positionCollector[i][1][positionCollector[i][1].Count -1] 
                    mod0 = positionCollector[i][1][positionCollector[i][1].Count -1]   % 8
                    if mod0 > 0:   
                       numberToFind = positionCollector[i][1][positionCollector[i][1].Count -1]  -1
                       start = start +1
                    else:
                       numberToFind = positionCollector[i][1][positionCollector[i][1].Count -1]  +15
                       start = start +1
                break
    

    #collectorItems = positionCollector.Count -1
    #if currentValue < collectorItems:  
    if numberToFind < maxValueToAnalyse:

       if found == False: 
          if numberToFind - incrementor > 0:
             numberToFind = numberToFind -1 + incrementor
          else:
             if incrementor == 0:
                incrementor +=15
             else:
                incrementor +=16
             numberToFind =  incrementor - numberToFind

       orderBigEndian(positionCollector,numberToFind, start, incrementor, maxValueToAnalyse) 
    else: return
            

def create_AdminData(IntelCounter, MotorolaCounter, arraybitpositions, SortISignalIPduTxRx, GatewayCollections, frame, logFile):


        #Motorola
        #*******************************************************************************************************************************************
        if MotorolaCounter >0 and SortISignalIPduTxRx.Count > 2:
           positionCollector = []
           findthecorrectOrder = []

           maxValueToAnalyse = 0
           for bsort in xrange(1,len(SortISignalIPduTxRx)):
               if bsort >0:
                  if positionCollector.Count == 0:
                        positionCollectorIndex = 0
                  else:
                        positionCollectorIndex = positionCollector.Count 
                  o = arraybitpositions[positionCollectorIndex][1]
                  
                  if maxValueToAnalyse < arraybitpositions[positionCollectorIndex][1]:
                     maxValueToAnalyse = arraybitpositions[positionCollectorIndex][1]
                  positionCollector.append([SortISignalIPduTxRx[bsort]])
                  positionCollector[positionCollectorIndex].append(arraybitpositions[positionCollectorIndex])
           #reorder
           orderBigEndian(positionCollector, 7, 0, 0, maxValueToAnalyse)


           for i in xrange(0,len(positionCollector)):
               #SrtISignalIPduTxRx.append(positionCollector[i])
               SortISignalIPduTxRx[i+1] = positionCollector[i][0]
               arraybitpositions[i] = positionCollector[i][1]
        #*******************************************************************************************************************************************

        i = 0
        CountElements = SortISignalIPduTxRx.Count - 1
        if CountElements == 1:  # #Just one Signal "Not possible to search for "Gaps"
            
            CreateOneGatewayDescription(SortISignalIPduTxRx[1], GatewayCollections)

        elif CountElements > 1:  # #two ore more Signals

            ArrayCreateAdminData = []
            ArrayNotMergeableData = []

            while i < CountElements:

                 # >0 because 0 contains the ISignalIpdu name
                if i > 0:

                    # Check Source description must be in the same PDU

                    if (SortISignalIPduTxRx[i][0] == SortISignalIPduTxRx[i + 1][0]):
                        sameSourcePdu = True
                    else:
                        sameSourcePdu = False

                # Check Destination Description must be in the same PDU
                    if (SortISignalIPduTxRx[i][1] == SortISignalIPduTxRx[i + 1][1]):
                        sameDestinationPdu = True
                    else:
                        sameDestinationPdu = False
                # Check ComGwDestinationDescriptions must have the same

                    if (SortISignalIPduTxRx[i][20] == SortISignalIPduTxRx[i + 1][20]):
                        sameTransferProperty = True
                    else:

                        # ##- PENDING kann mit TRIGGERED bzw TRIGGERED-WITHOUT-REPETITION zusammengefasst werden


                         if format(SortISignalIPduTxRx[i][20]) == "eTriggeredWithoutRepetition" and format(SortISignalIPduTxRx[i + 1][20]) == "ePending" :
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "ePending" and format(SortISignalIPduTxRx[i + 1][20]) == "eTriggeredWithoutRepetition":
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "eTriggered" and format(SortISignalIPduTxRx[i + 1][20]) == "ePending" :
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "ePending" and format(SortISignalIPduTxRx[i + 1][20]) == "eTriggered":
                            sameTransferProperty = True

                         if format(SortISignalIPduTxRx[i][20]) == "eTriggeredWithoutRepetition" and format(SortISignalIPduTxRx[i + 1][20]) == "" :
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "" and format(SortISignalIPduTxRx[i + 1][20]) == "eTriggeredWithoutRepetition":
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "eTriggered" and format(SortISignalIPduTxRx[i + 1][20]) == "" :
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "" and format(SortISignalIPduTxRx[i + 1][20]) == "eTriggered":
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "" and format(SortISignalIPduTxRx[i + 1][20]) == "ePending" :
                            sameTransferProperty = True

                         elif format(SortISignalIPduTxRx[i][20]) == "ePending" and format(SortISignalIPduTxRx[i + 1][20]) == "":
                            sameTransferProperty = True

                         else:
                            sameTransferProperty = False

                # order signals reversed? not important anymore
                    byteShiftFirstSig   = (SortISignalIPduTxRx[i][19] // 8) - (SortISignalIPduTxRx[i][17] // 8)
                    byteShiftSecondSig  = (SortISignalIPduTxRx[i+1][19] // 8) - (SortISignalIPduTxRx[i+1][17] // 8)
                    bitShiftFirstSig    = (SortISignalIPduTxRx[i][19]) - (SortISignalIPduTxRx[i][17])
                    bitShiftSecondSig   = (SortISignalIPduTxRx[i+1][19]) - (SortISignalIPduTxRx[i+1][17])
                    sameLayout = False
                    if (byteShiftFirstSig == byteShiftSecondSig):
                        if (bitShiftFirstSig == bitShiftSecondSig):
                            sameLayout = True
                    elif ((byteShiftFirstSig < 0) or (byteShiftSecondSig < 0)):
                        if ((byteShiftFirstSig-byteShiftSecondSig == 1) and (bitShiftFirstSig-bitShiftSecondSig == 16)):
                            sameLayout = True
                    else:
                        if ((byteShiftFirstSig-byteShiftSecondSig == -1) and (bitShiftFirstSig-bitShiftSecondSig == -16)):
                            sameLayout = True

                    ###############Intel############################################################################
                    if (IntelCounter > 0 and MotorolaCounter == 0):
                    # Check There must be *no* gaps between mergeable
                    # Descriptions (source/destination)
                        lastPositionFirst = arraybitpositions[i - 1][arraybitpositions[i - 1].Count - 1]
                        firstPositionSecond = arraybitpositions[i][1]
                        s = firstPositionSecond - lastPositionFirst - 1

                        if (s == 0):
                            noGaps = True
                        else:
                            noGaps = False # bit gap

                        if (sameSourcePdu == True) and (sameDestinationPdu == True) and (sameTransferProperty == True) and (noGaps == True) and (sameLayout == True):

                            # verify if one was already added to the array
                            if (i == 1):
                                ArrayCreateAdminData.append(SortISignalIPduTxRx[i])
                                ArrayCreateAdminData.append(SortISignalIPduTxRx[i + 1])
                            else:
                                iExists = False
                                iplusoneExists = False
                                for ialreadyExists in ArrayCreateAdminData:
                                    if ialreadyExists[8] == SortISignalIPduTxRx[i][8] and ialreadyExists[9] == SortISignalIPduTxRx[i][9]:
                                       iExists = True
                                       break
                                if iExists == False:
                                    ArrayCreateAdminData.append(SortISignalIPduTxRx[i])

                                for iplusonealreadyExists in ArrayCreateAdminData:
                                    if iplusonealreadyExists[8] == SortISignalIPduTxRx[i + 1][8] and iplusonealreadyExists[9] == SortISignalIPduTxRx[i + 1][9]:  # signalipdumapping
                                       iplusoneExists = True
                                if iplusoneExists == False:
                                    ArrayCreateAdminData.append(SortISignalIPduTxRx[i + 1])

                                # remove from not mergeabledata if it can be merged with the consecutive ones.
                                indextoremove = 0
                                for indexremover in range(ArrayNotMergeableData.Count):
                                    if SortISignalIPduTxRx[i][8] == ArrayNotMergeableData[indexremover][8] and SortISignalIPduTxRx[i][9] == ArrayNotMergeableData[indexremover][9]:
                                       indextoremove = indexremover
                                       ArrayNotMergeableData.pop(indexremover)
                                       # "removed from arraynotmergabledata"
                                       break


                        else: 
                            
                            print "merge not posible"
                            logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                            logFile.write("\n merge between:")
                            logFile.write("\n SignalMapping 1 source: " +  SortISignalIPduTxRx[i][8].AsrPath + "target: " +  SortISignalIPduTxRx[i][9].AsrPath)
                            logFile.write("\n SignalMapping 2 source: " +  SortISignalIPduTxRx[i+1][8].AsrPath + "target: " +  SortISignalIPduTxRx[i+1][9].AsrPath + " not possible")
                            logFile.write("\n sameSourcePdu= " + str(sameSourcePdu) + "\n sameDestinationPdu =" +  str(sameDestinationPdu) + "\n sametransferProperty =" +  str(sameTransferProperty) + "\n noGaps:" + str(noGaps)  + "\n Same Layout:" + str(sameLayout))
                            logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                            logFile.write("\n") 
                            iExists = False
                            iplusoneExists = False
                            if (i == 1):
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i])
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i + 1])
                            else:

                                # #was the signal mapping merged already?
                                iwasmerged = False
                                for wmerged in ArrayCreateAdminData:
                                    if wmerged[8] == SortISignalIPduTxRx[i][8] and wmerged[9] == SortISignalIPduTxRx[i][9]:
                                        iwasmerged = True
                                        break
                                if iwasmerged == False:

                                    # is the signal which can not be merged
                                    # already in the "not mergable Data list?
                                    for ialreadyExists in ArrayNotMergeableData:
                                        if ialreadyExists[8] == SortISignalIPduTxRx[i][8]  and ialreadyExists[9] == SortISignalIPduTxRx[i][9]:
                                           iExists = True
                                           break
                                    if iExists == False:
                                       ArrayNotMergeableData.append(SortISignalIPduTxRx[i])

                                ###### new signal not compatible found(until now)
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i + 1])

                    #######################################################################
                            if ArrayCreateAdminData.Count > 1:
                               
                               CreateMultipleSignalRoutingDescriptions(ArrayCreateAdminData, GatewayCollections)
                               ArrayCreateAdminData = []
                    #######################################################################

                    ###############Motorola Intel###################################################################
                    elif (IntelCounter > 0 and MotorolaCounter > 0) or (IntelCounter == 0 and MotorolaCounter > 0):



                        if(IntelCounter > 0 and MotorolaCounter > 0):
                            # find Gaps in the mask
                            arrayfindGaps = []
                            indexPositions = 0
                            firstsignal = arraybitpositions[i - 1]
                            secondsignal = arraybitpositions[i]
                            ####print firstsignal.Count
                            for j in range(firstsignal.Count):
                               if j > 0:
                                  arrayfindGaps.append(firstsignal[j])

                            for k in range(secondsignal.Count):
                                if k > 0:
                                  arrayfindGaps.append(secondsignal[k])
                            arrayfindGaps.sort()
                            noGaps = True
                            for l in range(arrayfindGaps.Count - 1):
                                if not (arrayfindGaps[l] == arrayfindGaps[l + 1] - 1):
                                   findGap = findGapinMask(arrayfindGaps[l] + 1, arraybitpositions)
                                   if findGap == True:
                                      noGaps = True
                                      # break
                                   else:
                                       noGaps = False  # Gap found!
                                       break
                        elif(IntelCounter == 0 and MotorolaCounter > 0):
                             noGaps = findGapinMaskBigEndian(arraybitpositions[i - 1],arraybitpositions[i])


                        if (sameSourcePdu == True) and (sameDestinationPdu == True) and (noGaps == True) and (sameLayout == True):  # and (sameTransferProperty== True) for Motorola-Intel Case not required

                            # verify if one was already added to the array
                            if (i == 1):
                                ArrayCreateAdminData.append(SortISignalIPduTxRx[i])
                                ArrayCreateAdminData.append(SortISignalIPduTxRx[i + 1])
                            else:
                                iExists = False
                                iplusoneExists = False
                                for ialreadyExists in ArrayCreateAdminData:
                                    if ialreadyExists[8] == SortISignalIPduTxRx[i][8]  and ialreadyExists[9] == SortISignalIPduTxRx[i][9]:
                                       iExists = True
                                       break
                                if iExists == False:
                                    ArrayCreateAdminData.append(SortISignalIPduTxRx[i])

                                for iplusonealreadyExists in ArrayCreateAdminData:
                                    if iplusonealreadyExists[8] == SortISignalIPduTxRx[i + 1][8]  and iplusonealreadyExists[9] == SortISignalIPduTxRx[i][9]:  # signalipdumapping
                                       iplusoneExists = True
                                if iplusoneExists == False:
                                    ArrayCreateAdminData.append(SortISignalIPduTxRx[i + 1])

                                # remove from not mergeabledata if it can be merged with the consecutive ones.
                                indextoremove = 0
                                for indexremover in range(ArrayNotMergeableData.Count):
                                    if SortISignalIPduTxRx[i][8] == ArrayNotMergeableData[indexremover][8] and SortISignalIPduTxRx[i][9] == ArrayNotMergeableData[indexremover][9]:
                                       indextoremove = indexremover
                                       ArrayNotMergeableData.pop(indexremover)
                                       # "removed from arraynotmergabledata"
                                       break


                        else: 
                            
                            print "merge not posible"
                            logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                            logFile.write("\n merge between:")
                            logFile.write("\n SignalMapping 1 source: " +  SortISignalIPduTxRx[i][8].AsrPath + "target: " +  SortISignalIPduTxRx[i][9].AsrPath)
                            logFile.write("\n SignalMapping 2 source: " +  SortISignalIPduTxRx[i+1][8].AsrPath + "target: " +  SortISignalIPduTxRx[i+1][9].AsrPath + " not possible")
                            logFile.write("\n sameSourcePdu= " + str(sameSourcePdu) + "\n sameDestinationPdu =" +  str(sameDestinationPdu) + "\n sametransferProperty =" +  str(sameTransferProperty) + "\n noGaps:" + str(noGaps)  + "\n Same Layout:" + str(sameLayout) )
                            logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                            logFile.write("\n") 
                            iExists = False
                            iplusoneExists = False
                            if (i == 1):
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i])
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i + 1])
                            else:

                                # #was the signal mapping merged already?
                                iwasmerged = False
                                for wmerged in ArrayCreateAdminData:
                                    if wmerged[8] == SortISignalIPduTxRx[i][8] and wmerged[9] == SortISignalIPduTxRx[i][9]:
                                        iwasmerged = True
                                        break
                                if iwasmerged == False:

                                    # is the signal which can not be merged
                                    # already in the "not mergable Data list?
                                    for ialreadyExists in ArrayNotMergeableData:
                                        if ialreadyExists[8] == SortISignalIPduTxRx[i][8] and ialreadyExists[9] == SortISignalIPduTxRx[i][9]:
                                           iExists = True
                                           break
                                    if iExists == False:
                                       ArrayNotMergeableData.append(SortISignalIPduTxRx[i])

                                ###### new signal not compatible found(until now)
                                ArrayNotMergeableData.append(SortISignalIPduTxRx[i + 1])

                    #######################################################################
                            if ArrayCreateAdminData.Count > 1:
                               logFile.write("\n ") 
                               logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                               logFile.write("\n for the ISignalIPdu {0} {1} signals will be merged".format(ArrayCreateAdminData[0][0].AsrPath,str(ArrayCreateAdminData.Count)))
                               for item in ArrayCreateAdminData:
                                   #if  i > 0 :

                                  logFile.write("\n ************************************************************") 
                                  logFile.write("\n ***SignalMapping Source  --> {0} with Start bit position {1} , Signal Length {2} , Endianness {3}".format(item[8].AsrPath, item[19], item[5], item[11]))
                                  logFile.write("\n ***SignalMapping Target --> {0} with StartBit Position {1} , Signal Length {2}, Endianness {3} ".format(item[9].AsrPath, item[17], item[7], item[10]))
                                  logFile.write("\n ************************************************************") 
                               logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
                               logFile.write("\n ") 
                               
                               CreateMultipleSignalRoutingDescriptions(ArrayCreateAdminData, GatewayCollections)
                               ArrayCreateAdminData = []
                    #######################################################################

                i += 1
            if ArrayNotMergeableData.Count > 0:
               for notmergable in ArrayNotMergeableData:
                   
                   CreateOneGatewayDescription(notmergable, GatewayCollections)

            if ArrayCreateAdminData.Count > 1:

               logFile.write("\n ") 
               logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
               logFile.write("\n for the ISignalIPdu {0} {1} signals will be merged".format(ArrayCreateAdminData[0][0].AsrPath,str(ArrayCreateAdminData.Count)))
               for item in ArrayCreateAdminData:
                    #if  i > 0 :

                   logFile.write("\n ************************************************************") 
                   logFile.write("\n ***SignalMapping Source  --> {0} with Start bit position {1} , Signal Length {2} , Endianness {3}".format(item[8].AsrPath, item[19], item[5], item[11]))
                   logFile.write("\n ***SignalMapping Target --> {0} with StartBit Position {1} , Signal Length {2}, Endianness {3} ".format(item[9].AsrPath, item[17], item[7], item[10]))
                   logFile.write("\n ************************************************************") 
               logFile.write("\n ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------") 
               logFile.write("\n ") 
               
               CreateMultipleSignalRoutingDescriptions(ArrayCreateAdminData, GatewayCollections)

            elif ArrayCreateAdminData.count == 1 :
                CreateOneGatewayDescription(ArrayCreateAdminData, GatewayCollections)        

def findGapinMask(possibleGap, arraybitpositions):
    found = False
    for i in range(arraybitpositions.Count):
        if i > 0:
            for bitposition in arraybitpositions[i - 1]:
                # if bitposition > 0:
                if bitposition == possibleGap:
                    found = True  # no gap, bit found in mask!
                    return found
                    break
                else:
                    found = False
    return found


def findGapinMaskBigEndian(firstSignal, secondSignal):    
    nogap = False                                                   

    mod0 = firstSignal[firstSignal.Count-1] % 8
    mod7 = firstSignal[1] % 8

    if (mod0 == 0):
        if ((firstSignal[firstSignal.Count-1]+15) == (secondSignal[1])):
            nogap = True
    else:
        if ((firstSignal[firstSignal.Count-1]- 1) == (secondSignal[1])):
            nogap = True

    if (mod7 == 7):
        if ((firstSignal[1]-15) == (secondSignal[secondSignal.Count-1])):
            nogap = True
    else:
        if ((firstSignal[1]+ 1) == (secondSignal[secondSignal.Count-1])):
            nogap = True


    return nogap


def CreateMultipleSignalRoutingDescriptions(ArrayCreateAdminData, GatewayCollections):
    for Gateway in GatewayCollections:
        NewSDG = Gateway.AdminData.AddNewSdg()

        NewSDG.GidSpecified = True
        NewSDG.Gid = "DV:ComGwConfiguration"
        NewSDG.SdgContentsTypeSpecified = True
        # SortISignalIPduTxRx[0][5]
        Bitsize = 0

        for i in range(ArrayCreateAdminData.Count):
            BitLengthtoSum = format(ArrayCreateAdminData[i][5])
            Bitsize = Bitsize + int(BitLengthtoSum)

        ####NameSourceDescription pattern--> <SignalIPdu.ShortName>_<Signal.StartPosition(0x0B)>_<Signal.Length(0x03)>
                   
        SourceSignallengthHex =  hex(Bitsize) 
        DestinationSignallengthHex = hex(Bitsize) 

        NameSourceDescription = str(format(ArrayCreateAdminData[0][0].ShortName) + "_0x0" + format(ArrayCreateAdminData[0][17]) + "_" + SourceSignallengthHex)
        NameDestinationDescription = str(format(ArrayCreateAdminData[0][1].ShortName) + "_0x0" + format(ArrayCreateAdminData[0][19]) + "_" + DestinationSignallengthHex)

        NewSourceIPduRefSD = NewSDG.SdgContentsType.AddNewSd()
        NewSourceIPduRefSD.GidSpecified = True
        NewSourceIPduRefSD.Gid = "DV:ComGwSourceIPduRef"
        NewSourceIPduRefSD.Value = ArrayCreateAdminData[0][14].AsrPath  # #or LongName?

        NewDestinationIPduRefSD = NewSDG.SdgContentsType.AddNewSd()
        NewDestinationIPduRefSD.GidSpecified = True
        NewDestinationIPduRefSD.Gid = "DV:ComGwDestinationIPduRef"
        NewDestinationIPduRefSD.Value = ArrayCreateAdminData[0][15].AsrPath

        NewSourceBitSizeSD = NewSDG.SdgContentsType.AddNewSd()
        NewSourceBitSizeSD.GidSpecified = True
        NewSourceBitSizeSD.Gid = "DV:ComGwSourceBitSize"
        NewSourceBitSizeSD.Value = str(Bitsize)

        NewSourceBitPositionSD = NewSDG.SdgContentsType.AddNewSd()
        NewSourceBitPositionSD.GidSpecified = True
        NewSourceBitPositionSD.Gid = "DV:ComGwSourceBitPosition"
        NewSourceBitPositionSD.Value = format(ArrayCreateAdminData[0][17])

        NewDestinationBitPositionSD = NewSDG.SdgContentsType.AddNewSd()
        NewDestinationBitPositionSD.GidSpecified = True
        NewDestinationBitPositionSD.Gid = "DV:ComGwDestinationBitPosition"
        NewDestinationBitPositionSD.Value = format(ArrayCreateAdminData[0][19])


        NewSourceSignalendiannessSD = NewSDG.SdgContentsType.AddNewSd()
        NewSourceSignalendiannessSD.GidSpecified = True
        NewSourceSignalendiannessSD.Gid = "DV:ComGwSourceSignalEndianness"

        endiannessSource = str(ArrayCreateAdminData[0][8].PackingByteOrder)
        if endiannessSource == "eMostSignificantByteLast":  # intel
            NewSourceSignalendiannessSD.Value = "LITTLE_ENDIAN"
        else:
            NewSourceSignalendiannessSD.Value = "BIG_ENDIAN"


        NewDestinationSignalendiannessSD = NewSDG.SdgContentsType.AddNewSd()
        NewDestinationSignalendiannessSD.GidSpecified = True
        NewDestinationSignalendiannessSD.Gid = "DV:ComGwDestinationSignalEndianness"

        endiannessDestination = str(ArrayCreateAdminData[0][9].PackingByteOrder)
        if endiannessDestination == "eMostSignificantByteLast":  # intel
            NewDestinationSignalendiannessSD.Value = "LITTLE_ENDIAN"
        else:
            NewDestinationSignalendiannessSD.Value = "BIG_ENDIAN"

        NewSourceDescriptionSD = NewSDG.SdgContentsType.AddNewSd()
        NewSourceDescriptionSD.GidSpecified = True
        NewSourceDescriptionSD.Gid = "DV:ComGwSourceDescription"
        NewSourceDescriptionSD.Value = NameSourceDescription

        NewDestinationDescriptionSD = NewSDG.SdgContentsType.AddNewSd()
        NewDestinationDescriptionSD.GidSpecified = True
        NewDestinationDescriptionSD.Gid = "DV:ComGwDestinationDescription"
        NewDestinationDescriptionSD.Value = NameDestinationDescription

        NewDestinationTransferPropertySD = NewSDG.SdgContentsType.AddNewSd()
        NewDestinationTransferPropertySD.GidSpecified = True
        NewDestinationTransferPropertySD.Gid = "DV:ComGwDestinationTransferProperty"

        

        if format(ArrayCreateAdminData[0][20]) == "eTriggeredWithoutRepetition":
            NewDestinationTransferPropertySD.Value = "TRIGGERED_WITHOUT_REPETITION"

        elif format(ArrayCreateAdminData[0][20]) == "eTriggeredOnChangeWithoutRepetition":
            NewDestinationTransferPropertySD.Value = "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION"

        elif format(ArrayCreateAdminData[0][20]) == "eTriggeredOnChange":
            NewDestinationTransferPropertySD.Value = "TRIGGERED_ON_CHANGE"

        elif format(ArrayCreateAdminData[0][20]) == "eTriggered":
            NewDestinationTransferPropertySD.Value = "TRIGGERED"

        elif format(ArrayCreateAdminData[0][20]) == "ePending":
            NewDestinationTransferPropertySD.Value = "PENDING"

        for k in range(ArrayCreateAdminData.Count):
            NewSignalMappingrefSDG = NewSDG.SdgContentsType.AddNewSdg()
            NewSignalMappingrefSDG.GidSpecified = True
            NewSignalMappingrefSDG.Gid = "DV:ComGwMapping"
            NewSignalMappingrefSDG.SdgContentsTypeSpecified = True

            NewSourceSignalMapping = NewSignalMappingrefSDG.SdgContentsType.AddNewSd()
            NewSourceSignalMapping.GidSpecified = True
            NewSourceSignalMapping.Gid = "DV:ComGwSourceSignalRef"
            NewSourceSignalMapping.Value = format(ArrayCreateAdminData[k][2])  # #Source

            NewDestinationSignalMapping = NewSignalMappingrefSDG.SdgContentsType.AddNewSd()
            NewDestinationSignalMapping.GidSpecified = True
            NewDestinationSignalMapping.Gid = "DV:ComGwDestinationSignalRef"
            NewDestinationSignalMapping.Value = format(ArrayCreateAdminData[k][3])  # Destination

        if not (ArrayCreateAdminData[0][22] == "RxNoUpdateBit"):
           RxNoUpdateBitSD = NewSDG.SdgContentsType.AddNewSd()
           RxNoUpdateBitSD.GidSpecified = True
           RxNoUpdateBitSD.Gid = "DV:ComGwSourceUpdateBitPosition"
           RxNoUpdateBitSD.Value = format(str(ArrayCreateAdminData[0][22].SignedValue))

        if not (ArrayCreateAdminData[0][24] == "TxNoUpdateBit"):
           TxNoUpdateBitSD = NewSDG.SdgContentsType.AddNewSd()
           TxNoUpdateBitSD.GidSpecified = True
           TxNoUpdateBitSD.Gid = "DV:ComGwDestinationUpdateBitPosition"
           TxNoUpdateBitSD.Value = format(str(ArrayCreateAdminData[0][24].SignedValue))


def CreateOneGatewayDescription(SortISignalIPduTxRx, GatewayCollections):
            for Gateway in GatewayCollections:
                NewSDG = Gateway.AdminData.AddNewSdg()

                NewSDG.GidSpecified = True
                NewSDG.Gid = "DV:ComGwConfiguration"
                NewSDG.SdgContentsTypeSpecified = True
                BitSize = int(SortISignalIPduTxRx[5])
                SourceSignallengthHex = hex(SortISignalIPduTxRx[5]).rstrip("L")
                DestinationSignallengthHex = hex(SortISignalIPduTxRx[7]).rstrip("L")

                ####NameSourceDescription pattern--> ####<SignalIPdu.ShortName>_<Signal.StartPosition(0x0B)>_<Signal.Length(0x03)>
                NameSourceDescription = str(format(SortISignalIPduTxRx[0].ShortName) + "_0x0" + format(SortISignalIPduTxRx[17]) + "_" + SourceSignallengthHex)
                NameDestinationDescription = str(format(SortISignalIPduTxRx[1].ShortName) + "_0x0" + format(SortISignalIPduTxRx[19]) + "_" + DestinationSignallengthHex)

                NewSourceIPduRefSD = NewSDG.SdgContentsType.AddNewSd()
                NewSourceIPduRefSD.GidSpecified = True
                NewSourceIPduRefSD.Gid = "DV:ComGwSourceIPduRef"
                NewSourceIPduRefSD.Value = SortISignalIPduTxRx[14].AsrPath  # #or LongName?

                NewDestinationIPduRefSD = NewSDG.SdgContentsType.AddNewSd()
                NewDestinationIPduRefSD.GidSpecified = True
                NewDestinationIPduRefSD.Gid = "DV:ComGwDestinationIPduRef"
                NewDestinationIPduRefSD.Value = SortISignalIPduTxRx[15].AsrPath

                NewSourceBitSizeSD = NewSDG.SdgContentsType.AddNewSd()
                NewSourceBitSizeSD.GidSpecified = True
                NewSourceBitSizeSD.Gid = "DV:ComGwSourceBitSize"
                NewSourceBitSizeSD.Value = str(BitSize)

                NewSourceBitPositionSD = NewSDG.SdgContentsType.AddNewSd()
                NewSourceBitPositionSD.GidSpecified = True
                NewSourceBitPositionSD.Gid = "DV:ComGwSourceBitPosition"
                NewSourceBitPositionSD.Value = format(SortISignalIPduTxRx[17])

                NewDestinationBitPositionSD = NewSDG.SdgContentsType.AddNewSd()
                NewDestinationBitPositionSD.GidSpecified = True
                NewDestinationBitPositionSD.Gid = "DV:ComGwDestinationBitPosition"
                NewDestinationBitPositionSD.Value = format(SortISignalIPduTxRx[19])

                NewSourceSignalendiannessSD = NewSDG.SdgContentsType.AddNewSd()
                NewSourceSignalendiannessSD.GidSpecified = True
                NewSourceSignalendiannessSD.Gid = "DV:ComGwSourceSignalEndianness"

                endiannessSource = str(SortISignalIPduTxRx[8].PackingByteOrder)

                if endiannessSource == "eMostSignificantByteLast":  # intel
                   NewSourceSignalendiannessSD.Value = "LITTLE_ENDIAN"
                else:
                   NewSourceSignalendiannessSD.Value = "BIG_ENDIAN"

                NewDestinationSignalendiannessSD = NewSDG.SdgContentsType.AddNewSd()
                NewDestinationSignalendiannessSD.GidSpecified = True
                NewDestinationSignalendiannessSD.Gid = "DV:ComGwDestinationSignalEndianness"

                endiannessDestination = str(SortISignalIPduTxRx[9].PackingByteOrder)
                if endiannessDestination == "eMostSignificantByteLast":  # intel
                   NewDestinationSignalendiannessSD.Value = "LITTLE_ENDIAN"
                else:
                   NewDestinationSignalendiannessSD.Value = "BIG_ENDIAN"

                NewSourceDescriptionSD = NewSDG.SdgContentsType.AddNewSd()
                NewSourceDescriptionSD.GidSpecified = True
                NewSourceDescriptionSD.Gid = "DV:ComGwSourceDescription"
                NewSourceDescriptionSD.Value = NameSourceDescription

                NewDestinationDescriptionSD = NewSDG.SdgContentsType.AddNewSd()
                NewDestinationDescriptionSD.GidSpecified = True
                NewDestinationDescriptionSD.Gid = "DV:ComGwDestinationDescription"
                NewDestinationDescriptionSD.Value = NameDestinationDescription

                NewDestinationTransferPropertySD = NewSDG.SdgContentsType.AddNewSd()
                NewDestinationTransferPropertySD.GidSpecified = True
                NewDestinationTransferPropertySD.Gid = "DV:ComGwDestinationTransferProperty"

                if format(SortISignalIPduTxRx[20]) == "eTriggeredWithoutRepetition":
                    NewDestinationTransferPropertySD.Value = "TRIGGERED_WITHOUT_REPETITION"

                elif format(SortISignalIPduTxRx[20]) == "eTriggeredOnChangeWithoutRepetition":
                    NewDestinationTransferPropertySD.Value = "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION"

                elif format(SortISignalIPduTxRx[20]) == "eTriggeredOnChange":
                    NewDestinationTransferPropertySD.Value = "TRIGGERED_ON_CHANGE"

                elif format(SortISignalIPduTxRx[20]) == "eTriggered":
                    NewDestinationTransferPropertySD.Value = "TRIGGERED"

                elif format(SortISignalIPduTxRx[20]) == "ePending":
                    NewDestinationTransferPropertySD.Value = "PENDING"

                # #SDG SignalMapping
                NewSignalMappingrefSDG = NewSDG.SdgContentsType.AddNewSdg()
                NewSignalMappingrefSDG.GidSpecified = True
                NewSignalMappingrefSDG.Gid = "DV:ComGwMapping"
                NewSignalMappingrefSDG.SdgContentsTypeSpecified = True

                NewSourceSignalMapping = NewSignalMappingrefSDG.SdgContentsType.AddNewSd()
                NewSourceSignalMapping.GidSpecified = True
                NewSourceSignalMapping.Gid = "DV:ComGwSourceSignalRef"
                NewSourceSignalMapping.Value = format(SortISignalIPduTxRx[2])  # #Source

                NewDestinationSignalMapping = NewSignalMappingrefSDG.SdgContentsType.AddNewSd()
                NewDestinationSignalMapping.GidSpecified = True
                NewDestinationSignalMapping.Gid = "DV:ComGwDestinationSignalRef"
                NewDestinationSignalMapping.Value = format(SortISignalIPduTxRx[3])  # Destination



                if not (SortISignalIPduTxRx[22] == "RxNoUpdateBit"):
                   RxNoUpdateBitSD = NewSDG.SdgContentsType.AddNewSd()
                   RxNoUpdateBitSD.GidSpecified = True
                   RxNoUpdateBitSD.Gid = "DV:ComGwSourceUpdateBitPosition"
                   RxNoUpdateBitSD.Value = format(str(SortISignalIPduTxRx[22].SignedValue))

                if not (SortISignalIPduTxRx[24] == "TxNoUpdateBit"):
                   TxNoUpdateBitSD = NewSDG.SdgContentsType.AddNewSd()
                   TxNoUpdateBitSD.GidSpecified = True
                   TxNoUpdateBitSD.Gid = "DV:ComGwDestinationUpdateBitPosition"
                   TxNoUpdateBitSD.Value = format(str(SortISignalIPduTxRx[24].SignedValue))


def check_preconditions(ISignalToIPduMappingRx, ISignalToIPduMappingTx):


    fulfilled_PreconditionsCounter = 0

    ###WARNING-----> Start Bit position is not important anymore -----> discarded!!!!

    # Compare ISignalIpduMappings
    # A Com Signal Routing must fulfill following preconditions to become a Com Description Routing
    # 1- -> The StartBit of the Source and the Destination ComSignal/ComSignalGroup
    # 2- must have the same Bit in Byte position.  (Source StartBit %8 ) == (Destination StartBit %8).


    #PositionInByteTx = int((ISignalToIPduMappingTx.StartPosition.SignedValue) % 8)
    #PositionInByteRx = int((ISignalToIPduMappingRx.StartPosition.SignedValue) % 8)

    #if not PositionInByteTx == PositionInByteRx:

    # if not ISignalToIPduMappingTx.StartPosition == #ISignalToIPduMappingRx.StartPosition:
    #    fulfilled_PreconditionsCounter += 1
    #    CheckStartBitSourceDestination = False
    #else:
    CheckStartBitSourceDestination = True
    # -> The endianness of the Source and Destination Signal must be equal.

    if not ISignalToIPduMappingTx.PackingByteOrder == ISignalToIPduMappingRx.PackingByteOrder:
        fulfilled_PreconditionsCounter += 1
        CheckendiannessSourceDestination = False
    else:
        CheckendiannessSourceDestination = True

    # -> The Source and the Destination Signal must not have an Update Bit (not important anymore)
    #if not ISignalToIPduMappingTx.UpdateIndicationBitPositionSpecified == False and ISignalToIPduMappingRx.UpdateIndicationBitPositionSpecified == False:
        #fulfilled_PreconditionsCounter += 1
        #CheckUpdateBitSourceDestination = False
    #else:
    CheckUpdateBitSourceDestination = True

    # -> The Source and the Destination Signal must not have Filter
    ##################################################################################################################################################################################################################
    IsignalIPduTx = ISignalToIPduMappingTx.Owner
    CheckFilterTxSourceDestination = True
    for PduTimingSpecListTx in IsignalIPduTx.IPduTimingSpecificationList:
        if PduTimingSpecListTx.TransmissionModeDeclarationSpecified == True:
            if PduTimingSpecListTx.TransmissionModeDeclaration.TransmissionModeConditionList.Count == 0:
                CheckFilterTxSourceDestination = True
            else:
                transmissionModeConditionList =  PduTimingSpecListTx.TransmissionModeDeclaration.TransmissionModeConditionList
                allFiltersTxAlwaysOrNever = True     #Boolean 
                for transmissionModeCondition in transmissionModeConditionList:
                    if transmissionModeCondition.DataFilterSpecified == True:
                        if not format(transmissionModeCondition.DataFilter.DataFilterType) == "eAlways" or not format(transmissionModeCondition.DataFilter.DataFilterType == "eNever"):
                            allFiltersTxAlwaysOrNever = False
                            break
                if allFiltersTxAlwaysOrNever == False:
                   CheckFilterTxSourceDestination = False
                   break

    IsignalIPduRx = ISignalToIPduMappingRx.Owner
    CheckFilterRxSourceDestination = True

    for PduTimingSpecListRx in IsignalIPduRx.IPduTimingSpecificationList:
        if PduTimingSpecListRx.TransmissionModeDeclarationSpecified == True:
            if PduTimingSpecListRx.TransmissionModeDeclaration.TransmissionModeConditionList.Count == 0:
                CheckFilterRxSourceDestination = True
            else:
                transmissionModeConditionList =  PduTimingSpecListRx.TransmissionModeDeclaration.TransmissionModeConditionList
                allFiltersRxAlwaysOrNever = True     #Boolean 
                for transmissionModeCondition in transmissionModeConditionList:
                    if transmissionModeCondition.DataFilterSpecified == True:
                        if not format(transmissionModeCondition.DataFilter.DataFilterType) == "eAlways" or not format(transmissionModeCondition.DataFilter.DataFilterType == "eNever"):
                            allFiltersTxAlwaysOrNever = False
                            break
                if allFiltersRxAlwaysOrNever == False:
                    CheckFilterRxSourceDestination = False
                    break
               
    if CheckFilterRxSourceDestination == True and CheckFilterTxSourceDestination == True:
       CheckFilterSourceDestination = True
    else:
       CheckFilterSourceDestination = False
       fulfilled_PreconditionsCounter += 1

    ##################################################################################################################################################################################################################



    # -> The Source and the Destination Signal must not be contained in a TP Pdu
    ##################################################################################################################################################################################################################
    CheckInTPPduSourceDestination = True
    for referencedElements in IsignalIPduRx.ReferencedFromList:
        if isinstance(referencedElements.Owner.Owner, VLinTpConfig) or isinstance(referencedElements.Owner.Owner, VCanTpConfig) or isinstance(referencedElements.Owner.Owner,VFlexrayTpConfig):                  
            CheckInTPPduSourceDestination = False
        if CheckInTPPduSourceDestination == False:
           fulfilled_PreconditionsCounter += 1
    ##################################################################################################################################################################################################################


    ##################################################################################################################################################################################################################
    if fulfilled_PreconditionsCounter == 0: 
       return fulfilled_PreconditionsCounter
    ##################################################################################################################################################################################################################

def saveISignalIPduRxCollection(ISignalIPduRx , ISignalIPduRxCollectorArray, RxPropertiesCollectorRxPropertiesCollectorIndex):

    counterISignalIPduRxFound = 0
    index = 0
    for PacketRx in ISignalIPduRxCollectorArray:
        
        #if ISIgnalIpdu already exists in collection
        if  PacketRx[0] == ISignalIPduRx:
            counterISignalIPduRxFound += 1
            ISignalIPduRxCollectorArray[index].append(RxPropertiesCollectorRxPropertiesCollectorIndex)
            break
        index += 1
    if counterISignalIPduRxFound == 0:
       # ADD NEW
       ISignalIPduRxCollectorArray.append([])
       ISignalIPduRxCollectorArray[index].append(ISignalIPduRx)
       ISignalIPduRxCollectorArray[index].append(RxPropertiesCollectorRxPropertiesCollectorIndex)


def Execute():
    try: 

        GatewayCollections = []
        #log file    
        ##################################################################################################################################################################################################################
        FilenameDescriptionRoutings = "{0}/" + "logFileDescriptionRoutings.txt"
        logFile = open(FilenameDescriptionRoutings.format(os.path.dirname(os.path.realpath(__file__))), "w")
        
        ##################################################################################################################################################################################################################
        logFile.write("\n searching for AUTOSAR Elements......") 
        logFile.write("\n ***************************************************************************************************************************************************************************************") 
        logFile.write("\n ") 

              

        FindFirstARPackage(logFile, GatewayCollections)
        
        GatewayAdminData = GatewayCollections[0].AdminData
        logFile.write("\n ComDescriptionRoutings created ---> " + str(GatewayAdminData.SdgList.Count))
        logFile.write("\n Script execution completed successfully")
        Log("Script execution completed successfully")
        
        
                        

    except Exception, e:
        Log(e.message)
Execute()    