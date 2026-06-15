//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/common/LteCommonEnum.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LteCommonEnum_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace simu5g {

Register_Enum(simu5g::Direction, (simu5g::Direction::DL, simu5g::Direction::UL, simu5g::Direction::D2D, simu5g::Direction::D2D_MULTI, simu5g::Direction::UNKNOWN_DIRECTION));

Register_Enum(simu5g::LteMod, (simu5g::LteMod::_QPSK, simu5g::LteMod::_16QAM, simu5g::LteMod::_64QAM, simu5g::LteMod::_256QAM));

Register_Enum(simu5g::FeedbackType, (simu5g::FeedbackType::ALLBANDS, simu5g::FeedbackType::PREFERRED, simu5g::FeedbackType::WIDEBAND));

Register_Enum(simu5g::FbPeriodicity, (simu5g::FbPeriodicity::PERIODIC, simu5g::FbPeriodicity::APERIODIC));

Register_Enum(simu5g::RbAllocationType, (simu5g::RbAllocationType::TYPE2_DISTRIBUTED, simu5g::RbAllocationType::TYPE2_LOCALIZED));

Register_Enum(simu5g::LteTrafficClass, (simu5g::LteTrafficClass::CONVERSATIONAL, simu5g::LteTrafficClass::STREAMING, simu5g::LteTrafficClass::INTERACTIVE, simu5g::LteTrafficClass::BACKGROUND, simu5g::LteTrafficClass::UNKNOWN_TRAFFIC_TYPE));

Register_Enum(simu5g::GrantType, (simu5g::GrantType::FITALL, simu5g::GrantType::FIXED_, simu5g::GrantType::URGENT, simu5g::GrantType::UNKNOWN_GRANT_TYPE));

Register_Enum(simu5g::LteRlcType, (simu5g::LteRlcType::TM, simu5g::LteRlcType::UM, simu5g::LteRlcType::AM, simu5g::LteRlcType::UNKNOWN_RLC_TYPE));

Register_Enum(simu5g::UlTransmissionMapTTI, (simu5g::UlTransmissionMapTTI::PREV_TTI, simu5g::UlTransmissionMapTTI::CURR_TTI));

Register_Enum(simu5g::LteD2DMode, (simu5g::LteD2DMode::NONE, simu5g::LteD2DMode::IM, simu5g::LteD2DMode::DM));

Register_Enum(simu5g::ApplicationType, (simu5g::ApplicationType::VOIP, simu5g::ApplicationType::VOD, simu5g::ApplicationType::WEB, simu5g::ApplicationType::CBR, simu5g::ApplicationType::FTP, simu5g::ApplicationType::GAMING, simu5g::ApplicationType::FULLBUFFER, simu5g::ApplicationType::UNKNOWN_APP));

Register_Enum(simu5g::SchedDiscipline, (simu5g::SchedDiscipline::DRR, simu5g::SchedDiscipline::PF, simu5g::SchedDiscipline::MAXCI, simu5g::SchedDiscipline::MAXCI_MB, simu5g::SchedDiscipline::MAXCI_OPT_MB, simu5g::SchedDiscipline::MAXCI_COMP, simu5g::SchedDiscipline::ALLOCATOR_BESTFIT, simu5g::SchedDiscipline::UNKNOWN_DISCIPLINE));

Register_Enum(simu5g::PilotComputationModes, (simu5g::PilotComputationModes::MIN_CQI, simu5g::PilotComputationModes::MAX_CQI, simu5g::PilotComputationModes::AVG_CQI, simu5g::PilotComputationModes::MEDIAN_CQI, simu5g::PilotComputationModes::ROBUST_CQI));

Register_Enum(simu5g::TxMode, (simu5g::TxMode::SINGLE_ANTENNA_PORT0, simu5g::TxMode::SINGLE_ANTENNA_PORT5, simu5g::TxMode::TRANSMIT_DIVERSITY, simu5g::TxMode::OL_SPATIAL_MULTIPLEXING, simu5g::TxMode::CL_SPATIAL_MULTIPLEXING, simu5g::TxMode::MULTI_USER, simu5g::TxMode::UNKNOWN_TX_MODE));

Register_Enum(simu5g::TxDirectionType, (simu5g::TxDirectionType::ANISOTROPIC, simu5g::TxDirectionType::OMNI, simu5g::TxDirectionType::UNKNOWN_TX_DIRECTION));

Register_Enum(simu5g::FeedbackGeneratorType, (simu5g::FeedbackGeneratorType::IDEAL, simu5g::FeedbackGeneratorType::REAL, simu5g::FeedbackGeneratorType::DAS_AWARE, simu5g::FeedbackGeneratorType::UNKNOW_FB_GEN_TYPE));

Register_Enum(simu5g::Plane, (simu5g::Plane::MAIN_PLANE, simu5g::Plane::MU_MIMO_PLANE));

Register_Enum(simu5g::DeploymentScenario, (simu5g::DeploymentScenario::INDOOR_HOTSPOT, simu5g::DeploymentScenario::URBAN_MICROCELL, simu5g::DeploymentScenario::URBAN_MACROCELL, simu5g::DeploymentScenario::RURAL_MACROCELL, simu5g::DeploymentScenario::SUBURBAN_MACROCELL, simu5g::DeploymentScenario::UNKNOW_SCENARIO));

Register_Enum(simu5g::Remote, (simu5g::Remote::MACRO, simu5g::Remote::RU1, simu5g::Remote::RU2, simu5g::Remote::RU3, simu5g::Remote::RU4, simu5g::Remote::RU5, simu5g::Remote::RU6, simu5g::Remote::UNKNOWN_RU));

Register_Enum(simu5g::LtePhyFrameType, (simu5g::LtePhyFrameType::DATAPKT, simu5g::LtePhyFrameType::BROADCASTPKT, simu5g::LtePhyFrameType::FEEDBACKPKT, simu5g::LtePhyFrameType::HANDOVERPKT, simu5g::LtePhyFrameType::HARQPKT, simu5g::LtePhyFrameType::GRANTPKT, simu5g::LtePhyFrameType::RACPKT, simu5g::LtePhyFrameType::D2DMODESWITCHPKT, simu5g::LtePhyFrameType::UNKNOWN_TYPE));

Register_Enum(simu5g::RanNodeType, (simu5g::RanNodeType::INTERNET, simu5g::RanNodeType::ENODEB, simu5g::RanNodeType::GNODEB, simu5g::RanNodeType::UE, simu5g::RanNodeType::UNKNOWN_NODE_TYPE));

Register_Enum(simu5g::CoreNodeType, (simu5g::CoreNodeType::ENB, simu5g::CoreNodeType::PGW, simu5g::CoreNodeType::SGW, simu5g::CoreNodeType::GNB, simu5g::CoreNodeType::UPF, simu5g::CoreNodeType::UPF_MEC));

Register_Enum(simu5g::BsrType, (simu5g::BsrType::SHORT_BSR, simu5g::BsrType::D2D_SHORT_BSR, simu5g::BsrType::D2D_MULTI_SHORT_BSR));

Register_Enum(simu5g::HarqAcknowledgment, (simu5g::HarqAcknowledgment::HARQNACK, simu5g::HarqAcknowledgment::HARQACK));

Register_Enum(simu5g::TxHarqPduStatus, (simu5g::TxHarqPduStatus::TXHARQ_PDU_BUFFERED, simu5g::TxHarqPduStatus::TXHARQ_PDU_WAITING, simu5g::TxHarqPduStatus::TXHARQ_PDU_EMPTY, simu5g::TxHarqPduStatus::TXHARQ_PDU_SELECTED));

Register_Enum(simu5g::RxHarqPduStatus, (simu5g::RxHarqPduStatus::RXHARQ_PDU_EMPTY, simu5g::RxHarqPduStatus::RXHARQ_PDU_EVALUATING, simu5g::RxHarqPduStatus::RXHARQ_PDU_CORRECT, simu5g::RxHarqPduStatus::RXHARQ_PDU_CORRUPTED));

Register_Enum(simu5g::EnbType, (simu5g::EnbType::MACRO_ENB, simu5g::EnbType::MICRO_ENB));

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

