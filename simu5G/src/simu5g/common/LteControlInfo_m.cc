//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/common/LteControlInfo.msg.
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
#include "LteControlInfo_m.h"

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

Register_Class(LteControlInfo)

LteControlInfo::LteControlInfo() : ::inet::TagBase()
{
}

LteControlInfo::LteControlInfo(const LteControlInfo& other) : ::inet::TagBase(other)
{
    copy(other);
}

LteControlInfo::~LteControlInfo()
{
}

LteControlInfo& LteControlInfo::operator=(const LteControlInfo& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void LteControlInfo::copy(const LteControlInfo& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->direction = other.direction;
    this->d2dTxPeerId = other.d2dTxPeerId;
    this->d2dRxPeerId = other.d2dRxPeerId;
    this->application = other.application;
    this->traffic = other.traffic;
    this->rlcType = other.rlcType;
    this->lcid = other.lcid;
    this->multicastGroupId = other.multicastGroupId;
}

void LteControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->direction);
    doParsimPacking(b,this->d2dTxPeerId);
    doParsimPacking(b,this->d2dRxPeerId);
    doParsimPacking(b,this->application);
    doParsimPacking(b,this->traffic);
    doParsimPacking(b,this->rlcType);
    doParsimPacking(b,this->lcid);
    doParsimPacking(b,this->multicastGroupId);
}

void LteControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->direction);
    doParsimUnpacking(b,this->d2dTxPeerId);
    doParsimUnpacking(b,this->d2dRxPeerId);
    doParsimUnpacking(b,this->application);
    doParsimUnpacking(b,this->traffic);
    doParsimUnpacking(b,this->rlcType);
    doParsimUnpacking(b,this->lcid);
    doParsimUnpacking(b,this->multicastGroupId);
}

MacNodeId LteControlInfo::getSourceId() const
{
    return this->sourceId;
}

void LteControlInfo::setSourceId(MacNodeId sourceId)
{
    this->sourceId = sourceId;
}

MacNodeId LteControlInfo::getDestId() const
{
    return this->destId;
}

void LteControlInfo::setDestId(MacNodeId destId)
{
    this->destId = destId;
}

unsigned short LteControlInfo::getDirection() const
{
    return this->direction;
}

void LteControlInfo::setDirection(unsigned short direction)
{
    this->direction = direction;
}

MacNodeId LteControlInfo::getD2dTxPeerId() const
{
    return this->d2dTxPeerId;
}

void LteControlInfo::setD2dTxPeerId(MacNodeId d2dTxPeerId)
{
    this->d2dTxPeerId = d2dTxPeerId;
}

MacNodeId LteControlInfo::getD2dRxPeerId() const
{
    return this->d2dRxPeerId;
}

void LteControlInfo::setD2dRxPeerId(MacNodeId d2dRxPeerId)
{
    this->d2dRxPeerId = d2dRxPeerId;
}

unsigned short LteControlInfo::getApplication() const
{
    return this->application;
}

void LteControlInfo::setApplication(unsigned short application)
{
    this->application = application;
}

unsigned short LteControlInfo::getTraffic() const
{
    return this->traffic;
}

void LteControlInfo::setTraffic(unsigned short traffic)
{
    this->traffic = traffic;
}

unsigned short LteControlInfo::getRlcType() const
{
    return this->rlcType;
}

void LteControlInfo::setRlcType(unsigned short rlcType)
{
    this->rlcType = rlcType;
}

uint16_t LteControlInfo::getLcid() const
{
    return this->lcid;
}

void LteControlInfo::setLcid(uint16_t lcid)
{
    this->lcid = lcid;
}

int32_t LteControlInfo::getMulticastGroupId() const
{
    return this->multicastGroupId;
}

void LteControlInfo::setMulticastGroupId(int32_t multicastGroupId)
{
    this->multicastGroupId = multicastGroupId;
}

class LteControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_direction,
        FIELD_d2dTxPeerId,
        FIELD_d2dRxPeerId,
        FIELD_application,
        FIELD_traffic,
        FIELD_rlcType,
        FIELD_lcid,
        FIELD_multicastGroupId,
    };
  public:
    LteControlInfoDescriptor();
    virtual ~LteControlInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LteControlInfoDescriptor)

LteControlInfoDescriptor::LteControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteControlInfo)), "inet::TagBase")
{
    propertyNames = nullptr;
}

LteControlInfoDescriptor::~LteControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool LteControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteControlInfo *>(obj)!=nullptr;
}

const char **LteControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int LteControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_direction
        FD_ISEDITABLE,    // FIELD_d2dTxPeerId
        FD_ISEDITABLE,    // FIELD_d2dRxPeerId
        FD_ISEDITABLE,    // FIELD_application
        FD_ISEDITABLE,    // FIELD_traffic
        FD_ISEDITABLE,    // FIELD_rlcType
        FD_ISEDITABLE,    // FIELD_lcid
        FD_ISEDITABLE,    // FIELD_multicastGroupId
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *LteControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "direction",
        "d2dTxPeerId",
        "d2dRxPeerId",
        "application",
        "traffic",
        "rlcType",
        "lcid",
        "multicastGroupId",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int LteControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "direction") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "d2dTxPeerId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "d2dRxPeerId") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "application") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "traffic") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "rlcType") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "lcid") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "multicastGroupId") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *LteControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simu5g::MacNodeId",    // FIELD_sourceId
        "simu5g::MacNodeId",    // FIELD_destId
        "unsigned short",    // FIELD_direction
        "simu5g::MacNodeId",    // FIELD_d2dTxPeerId
        "simu5g::MacNodeId",    // FIELD_d2dRxPeerId
        "unsigned short",    // FIELD_application
        "unsigned short",    // FIELD_traffic
        "unsigned short",    // FIELD_rlcType
        "uint16",    // FIELD_lcid
        "int32",    // FIELD_multicastGroupId
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **LteControlInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_direction: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_application: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_traffic: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_rlcType: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LteControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_direction:
            if (!strcmp(propertyName, "enum")) return "Direction";
            if (!strcmp(propertyName, "enum")) return "simu5g::Direction";
            return nullptr;
        case FIELD_application:
            if (!strcmp(propertyName, "enum")) return "ApplicationType";
            if (!strcmp(propertyName, "enum")) return "simu5g::ApplicationType";
            return nullptr;
        case FIELD_traffic:
            if (!strcmp(propertyName, "enum")) return "LteTrafficClass";
            if (!strcmp(propertyName, "enum")) return "simu5g::LteTrafficClass";
            return nullptr;
        case FIELD_rlcType:
            if (!strcmp(propertyName, "enum")) return "LteRlcType";
            if (!strcmp(propertyName, "enum")) return "simu5g::LteRlcType";
            return nullptr;
        default: return nullptr;
    }
}

int LteControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LteControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteControlInfo'", field);
    }
}

const char *LteControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LteControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return int642string(num(pp->getSourceId()));
        case FIELD_destId: return int642string(num(pp->getDestId()));
        case FIELD_direction: return enum2string(pp->getDirection(), "simu5g::Direction");
        case FIELD_d2dTxPeerId: return int642string(num(pp->getD2dTxPeerId()));
        case FIELD_d2dRxPeerId: return int642string(num(pp->getD2dRxPeerId()));
        case FIELD_application: return enum2string(pp->getApplication(), "simu5g::ApplicationType");
        case FIELD_traffic: return enum2string(pp->getTraffic(), "simu5g::LteTrafficClass");
        case FIELD_rlcType: return enum2string(pp->getRlcType(), "simu5g::LteRlcType");
        case FIELD_lcid: return ulong2string(pp->getLcid());
        case FIELD_multicastGroupId: return long2string(pp->getMulticastGroupId());
        default: return "";
    }
}

void LteControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(MacNodeId(string2int64(value))); break;
        case FIELD_destId: pp->setDestId(MacNodeId(string2int64(value))); break;
        case FIELD_direction: pp->setDirection((simu5g::Direction)string2enum(value, "simu5g::Direction")); break;
        case FIELD_d2dTxPeerId: pp->setD2dTxPeerId(MacNodeId(string2int64(value))); break;
        case FIELD_d2dRxPeerId: pp->setD2dRxPeerId(MacNodeId(string2int64(value))); break;
        case FIELD_application: pp->setApplication((simu5g::ApplicationType)string2enum(value, "simu5g::ApplicationType")); break;
        case FIELD_traffic: pp->setTraffic((simu5g::LteTrafficClass)string2enum(value, "simu5g::LteTrafficClass")); break;
        case FIELD_rlcType: pp->setRlcType((simu5g::LteRlcType)string2enum(value, "simu5g::LteRlcType")); break;
        case FIELD_lcid: pp->setLcid(string2ulong(value)); break;
        case FIELD_multicastGroupId: pp->setMulticastGroupId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteControlInfo'", field);
    }
}

omnetpp::cValue LteControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return num(pp->getSourceId());
        case FIELD_destId: return num(pp->getDestId());
        case FIELD_direction: return (omnetpp::intval_t)(pp->getDirection());
        case FIELD_d2dTxPeerId: return num(pp->getD2dTxPeerId());
        case FIELD_d2dRxPeerId: return num(pp->getD2dRxPeerId());
        case FIELD_application: return (omnetpp::intval_t)(pp->getApplication());
        case FIELD_traffic: return (omnetpp::intval_t)(pp->getTraffic());
        case FIELD_rlcType: return (omnetpp::intval_t)(pp->getRlcType());
        case FIELD_lcid: return (omnetpp::intval_t)(pp->getLcid());
        case FIELD_multicastGroupId: return pp->getMulticastGroupId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteControlInfo' as cValue -- field index out of range?", field);
    }
}

void LteControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(MacNodeId(value.intValue())); break;
        case FIELD_destId: pp->setDestId(MacNodeId(value.intValue())); break;
        case FIELD_direction: pp->setDirection((simu5g::Direction)value.intValue()); break;
        case FIELD_d2dTxPeerId: pp->setD2dTxPeerId(MacNodeId(value.intValue())); break;
        case FIELD_d2dRxPeerId: pp->setD2dRxPeerId(MacNodeId(value.intValue())); break;
        case FIELD_application: pp->setApplication((simu5g::ApplicationType)value.intValue()); break;
        case FIELD_traffic: pp->setTraffic((simu5g::LteTrafficClass)value.intValue()); break;
        case FIELD_rlcType: pp->setRlcType((simu5g::LteRlcType)value.intValue()); break;
        case FIELD_lcid: pp->setLcid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_multicastGroupId: pp->setMulticastGroupId(omnetpp::checked_int_cast<int32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteControlInfo'", field);
    }
}

const char *LteControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LteControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteControlInfo *pp = omnetpp::fromAnyPtr<LteControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteControlInfo'", field);
    }
}

Register_Class(FlowControlInfo)

FlowControlInfo::FlowControlInfo() : ::simu5g::LteControlInfo()
{
}

FlowControlInfo::FlowControlInfo(const FlowControlInfo& other) : ::simu5g::LteControlInfo(other)
{
    copy(other);
}

FlowControlInfo::~FlowControlInfo()
{
}

FlowControlInfo& FlowControlInfo::operator=(const FlowControlInfo& other)
{
    if (this == &other) return *this;
    ::simu5g::LteControlInfo::operator=(other);
    copy(other);
    return *this;
}

void FlowControlInfo::copy(const FlowControlInfo& other)
{
    this->srcAddr = other.srcAddr;
    this->dstAddr = other.dstAddr;
    this->typeOfService = other.typeOfService;
    this->sequenceNumber = other.sequenceNumber;
    this->headerSize = other.headerSize;
    this->useNR = other.useNR;
}

void FlowControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::LteControlInfo::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->dstAddr);
    doParsimPacking(b,this->typeOfService);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->headerSize);
    doParsimPacking(b,this->useNR);
}

void FlowControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::LteControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->dstAddr);
    doParsimUnpacking(b,this->typeOfService);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->headerSize);
    doParsimUnpacking(b,this->useNR);
}

uint32_t FlowControlInfo::getSrcAddr() const
{
    return this->srcAddr;
}

void FlowControlInfo::setSrcAddr(uint32_t srcAddr)
{
    this->srcAddr = srcAddr;
}

uint32_t FlowControlInfo::getDstAddr() const
{
    return this->dstAddr;
}

void FlowControlInfo::setDstAddr(uint32_t dstAddr)
{
    this->dstAddr = dstAddr;
}

uint16_t FlowControlInfo::getTypeOfService() const
{
    return this->typeOfService;
}

void FlowControlInfo::setTypeOfService(uint16_t typeOfService)
{
    this->typeOfService = typeOfService;
}

unsigned int FlowControlInfo::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void FlowControlInfo::setSequenceNumber(unsigned int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int FlowControlInfo::getHeaderSize() const
{
    return this->headerSize;
}

void FlowControlInfo::setHeaderSize(int headerSize)
{
    this->headerSize = headerSize;
}

bool FlowControlInfo::getUseNR() const
{
    return this->useNR;
}

void FlowControlInfo::setUseNR(bool useNR)
{
    this->useNR = useNR;
}

class FlowControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_dstAddr,
        FIELD_typeOfService,
        FIELD_sequenceNumber,
        FIELD_headerSize,
        FIELD_useNR,
    };
  public:
    FlowControlInfoDescriptor();
    virtual ~FlowControlInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FlowControlInfoDescriptor)

FlowControlInfoDescriptor::FlowControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::FlowControlInfo)), "simu5g::LteControlInfo")
{
    propertyNames = nullptr;
}

FlowControlInfoDescriptor::~FlowControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool FlowControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowControlInfo *>(obj)!=nullptr;
}

const char **FlowControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int FlowControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcAddr
        FD_ISEDITABLE,    // FIELD_dstAddr
        FD_ISEDITABLE,    // FIELD_typeOfService
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_headerSize
        FD_ISEDITABLE,    // FIELD_useNR
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *FlowControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "dstAddr",
        "typeOfService",
        "sequenceNumber",
        "headerSize",
        "useNR",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int FlowControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "dstAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "typeOfService") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "headerSize") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "useNR") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *FlowControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32",    // FIELD_srcAddr
        "uint32",    // FIELD_dstAddr
        "uint16",    // FIELD_typeOfService
        "unsigned int",    // FIELD_sequenceNumber
        "int",    // FIELD_headerSize
        "bool",    // FIELD_useNR
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowControlInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlowControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlowControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FlowControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowControlInfo'", field);
    }
}

const char *FlowControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return ulong2string(pp->getSrcAddr());
        case FIELD_dstAddr: return ulong2string(pp->getDstAddr());
        case FIELD_typeOfService: return ulong2string(pp->getTypeOfService());
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_headerSize: return long2string(pp->getHeaderSize());
        case FIELD_useNR: return bool2string(pp->getUseNR());
        default: return "";
    }
}

void FlowControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(string2ulong(value)); break;
        case FIELD_dstAddr: pp->setDstAddr(string2ulong(value)); break;
        case FIELD_typeOfService: pp->setTypeOfService(string2ulong(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        case FIELD_headerSize: pp->setHeaderSize(string2long(value)); break;
        case FIELD_useNR: pp->setUseNR(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowControlInfo'", field);
    }
}

omnetpp::cValue FlowControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return (omnetpp::intval_t)(pp->getSrcAddr());
        case FIELD_dstAddr: return (omnetpp::intval_t)(pp->getDstAddr());
        case FIELD_typeOfService: return (omnetpp::intval_t)(pp->getTypeOfService());
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_headerSize: return pp->getHeaderSize();
        case FIELD_useNR: return pp->getUseNR();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowControlInfo' as cValue -- field index out of range?", field);
    }
}

void FlowControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dstAddr: pp->setDstAddr(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_typeOfService: pp->setTypeOfService(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_headerSize: pp->setHeaderSize(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_useNR: pp->setUseNR(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowControlInfo'", field);
    }
}

const char *FlowControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr FlowControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowControlInfo *pp = omnetpp::fromAnyPtr<FlowControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowControlInfo'", field);
    }
}

Register_Class(UserControlInfo)

UserControlInfo::UserControlInfo() : ::simu5g::LteControlInfo()
{
}

UserControlInfo::UserControlInfo(const UserControlInfo& other) : ::simu5g::LteControlInfo(other)
{
    copy(other);
}

UserControlInfo::~UserControlInfo()
{
    delete this->userTxParams;
}

UserControlInfo& UserControlInfo::operator=(const UserControlInfo& other)
{
    if (this == &other) return *this;
    ::simu5g::LteControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UserControlInfo::copy(const UserControlInfo& other)
{
    this->isNr_ = other.isNr_;
    this->carrierFrequency = other.carrierFrequency;
    this->acid = other.acid;
    this->cw = other.cw;
    this->txNumber = other.txNumber;
    this->ndi = other.ndi;
    this->isCorruptible_ = other.isCorruptible_;
    this->isBroadcast_ = other.isBroadcast_;
    this->deciderResult = other.deciderResult;
    this->blerTh = other.blerTh;
    this->blerValue = other.blerValue;
    this->txMode = other.txMode;
    this->frameType = other.frameType;
    this->txPower = other.txPower;
    this->d2dTxPower = other.d2dTxPower;
    this->totalGrantedBlocks = other.totalGrantedBlocks;
    this->grantId = other.grantId;
    delete this->userTxParams;
    this->userTxParams = other.userTxParams;
    if (this->userTxParams != nullptr) {
        this->userTxParams = new UserTxParams(*this->userTxParams);
    }
    this->grantedBlocks = other.grantedBlocks;
    this->coord = other.coord;
    this->feedbackReq = other.feedbackReq;
}

void UserControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::LteControlInfo::parsimPack(b);
    doParsimPacking(b,this->isNr_);
    doParsimPacking(b,this->carrierFrequency);
    doParsimPacking(b,this->acid);
    doParsimPacking(b,this->cw);
    doParsimPacking(b,this->txNumber);
    doParsimPacking(b,this->ndi);
    doParsimPacking(b,this->isCorruptible_);
    doParsimPacking(b,this->isBroadcast_);
    doParsimPacking(b,this->deciderResult);
    doParsimPacking(b,this->blerTh);
    doParsimPacking(b,this->blerValue);
    doParsimPacking(b,this->txMode);
    doParsimPacking(b,this->frameType);
    doParsimPacking(b,this->txPower);
    doParsimPacking(b,this->d2dTxPower);
    doParsimPacking(b,this->totalGrantedBlocks);
    doParsimPacking(b,this->grantId);
    doParsimPacking(b,this->userTxParams);
    doParsimPacking(b,this->grantedBlocks);
    doParsimPacking(b,this->coord);
    doParsimPacking(b,this->feedbackReq);
}

void UserControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::LteControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->isNr_);
    doParsimUnpacking(b,this->carrierFrequency);
    doParsimUnpacking(b,this->acid);
    doParsimUnpacking(b,this->cw);
    doParsimUnpacking(b,this->txNumber);
    doParsimUnpacking(b,this->ndi);
    doParsimUnpacking(b,this->isCorruptible_);
    doParsimUnpacking(b,this->isBroadcast_);
    doParsimUnpacking(b,this->deciderResult);
    doParsimUnpacking(b,this->blerTh);
    doParsimUnpacking(b,this->blerValue);
    doParsimUnpacking(b,this->txMode);
    doParsimUnpacking(b,this->frameType);
    doParsimUnpacking(b,this->txPower);
    doParsimUnpacking(b,this->d2dTxPower);
    doParsimUnpacking(b,this->totalGrantedBlocks);
    doParsimUnpacking(b,this->grantId);
    doParsimUnpacking(b,this->userTxParams);
    doParsimUnpacking(b,this->grantedBlocks);
    doParsimUnpacking(b,this->coord);
    doParsimUnpacking(b,this->feedbackReq);
}

bool UserControlInfo::isNr() const
{
    return this->isNr_;
}

void UserControlInfo::setIsNr(bool isNr)
{
    this->isNr_ = isNr;
}

::inet::GHz UserControlInfo::getCarrierFrequency() const
{
    return this->carrierFrequency;
}

void UserControlInfo::setCarrierFrequency(::inet::GHz carrierFrequency)
{
    this->carrierFrequency = carrierFrequency;
}

unsigned char UserControlInfo::getAcid() const
{
    return this->acid;
}

void UserControlInfo::setAcid(unsigned char acid)
{
    this->acid = acid;
}

unsigned char UserControlInfo::getCw() const
{
    return this->cw;
}

void UserControlInfo::setCw(unsigned char cw)
{
    this->cw = cw;
}

unsigned char UserControlInfo::getTxNumber() const
{
    return this->txNumber;
}

void UserControlInfo::setTxNumber(unsigned char txNumber)
{
    this->txNumber = txNumber;
}

bool UserControlInfo::getNdi() const
{
    return this->ndi;
}

void UserControlInfo::setNdi(bool ndi)
{
    this->ndi = ndi;
}

bool UserControlInfo::isCorruptible() const
{
    return this->isCorruptible_;
}

void UserControlInfo::setIsCorruptible(bool isCorruptible)
{
    this->isCorruptible_ = isCorruptible;
}

bool UserControlInfo::isBroadcast() const
{
    return this->isBroadcast_;
}

void UserControlInfo::setIsBroadcast(bool isBroadcast)
{
    this->isBroadcast_ = isBroadcast;
}

bool UserControlInfo::getDeciderResult() const
{
    return this->deciderResult;
}

void UserControlInfo::setDeciderResult(bool deciderResult)
{
    this->deciderResult = deciderResult;
}

double UserControlInfo::getBlerTh() const
{
    return this->blerTh;
}

void UserControlInfo::setBlerTh(double blerTh)
{
    this->blerTh = blerTh;
}

double UserControlInfo::getBlerValue() const
{
    return this->blerValue;
}

void UserControlInfo::setBlerValue(double blerValue)
{
    this->blerValue = blerValue;
}

unsigned short UserControlInfo::getTxMode() const
{
    return this->txMode;
}

void UserControlInfo::setTxMode(unsigned short txMode)
{
    this->txMode = txMode;
}

unsigned int UserControlInfo::getFrameType() const
{
    return this->frameType;
}

void UserControlInfo::setFrameType(unsigned int frameType)
{
    this->frameType = frameType;
}

double UserControlInfo::getTxPower() const
{
    return this->txPower;
}

void UserControlInfo::setTxPower(double txPower)
{
    this->txPower = txPower;
}

double UserControlInfo::getD2dTxPower() const
{
    return this->d2dTxPower;
}

void UserControlInfo::setD2dTxPower(double d2dTxPower)
{
    this->d2dTxPower = d2dTxPower;
}

unsigned int UserControlInfo::getTotalGrantedBlocks() const
{
    return this->totalGrantedBlocks;
}

void UserControlInfo::setTotalGrantedBlocks(unsigned int totalGrantedBlocks)
{
    this->totalGrantedBlocks = totalGrantedBlocks;
}

unsigned int UserControlInfo::getGrantId() const
{
    return this->grantId;
}

void UserControlInfo::setGrantId(unsigned int grantId)
{
    this->grantId = grantId;
}

const UserTxParams * UserControlInfo::getUserTxParams() const
{
    return this->userTxParams;
}

void UserControlInfo::setUserTxParams(UserTxParams * userTxParams)
{
// cplusplus {{
    // Code inserted at top of setUserTxParams(); allows silent overwrite of earlier object.
    delete this->userTxParams;
    this->userTxParams = nullptr;
// }}
    if (this->userTxParams != nullptr) throw omnetpp::cRuntimeError("setUserTxParams(): a value is already set, remove it first with removeUserTxParams()");
    this->userTxParams = userTxParams;
}

UserTxParams * UserControlInfo::removeUserTxParams()
{
    UserTxParams * retval = this->userTxParams;
    this->userTxParams = nullptr;
    return retval;
}

const RbMap& UserControlInfo::getGrantedBlocks() const
{
    return this->grantedBlocks;
}

void UserControlInfo::setGrantedBlocks(const RbMap& grantedBlocks)
{
    this->grantedBlocks = grantedBlocks;
}

const ::inet::Coord& UserControlInfo::getCoord() const
{
    return this->coord;
}

void UserControlInfo::setCoord(const ::inet::Coord& coord)
{
    this->coord = coord;
}

const FeedbackRequest& UserControlInfo::getFeedbackReq() const
{
    return this->feedbackReq;
}

void UserControlInfo::setFeedbackReq(const FeedbackRequest& feedbackReq)
{
    this->feedbackReq = feedbackReq;
}

class UserControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_isNr,
        FIELD_carrierFrequency,
        FIELD_acid,
        FIELD_cw,
        FIELD_txNumber,
        FIELD_ndi,
        FIELD_isCorruptible,
        FIELD_isBroadcast,
        FIELD_deciderResult,
        FIELD_blerTh,
        FIELD_blerValue,
        FIELD_txMode,
        FIELD_frameType,
        FIELD_txPower,
        FIELD_d2dTxPower,
        FIELD_totalGrantedBlocks,
        FIELD_grantId,
        FIELD_userTxParams,
        FIELD_grantedBlocks,
        FIELD_coord,
        FIELD_feedbackReq,
    };
  public:
    UserControlInfoDescriptor();
    virtual ~UserControlInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(UserControlInfoDescriptor)

UserControlInfoDescriptor::UserControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::UserControlInfo)), "simu5g::LteControlInfo")
{
    propertyNames = nullptr;
}

UserControlInfoDescriptor::~UserControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool UserControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UserControlInfo *>(obj)!=nullptr;
}

const char **UserControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UserControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UserControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 21+base->getFieldCount() : 21;
}

unsigned int UserControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isNr
        FD_ISEDITABLE,    // FIELD_carrierFrequency
        FD_ISEDITABLE,    // FIELD_acid
        FD_ISEDITABLE,    // FIELD_cw
        FD_ISEDITABLE,    // FIELD_txNumber
        FD_ISEDITABLE,    // FIELD_ndi
        FD_ISEDITABLE,    // FIELD_isCorruptible
        FD_ISEDITABLE,    // FIELD_isBroadcast
        FD_ISEDITABLE,    // FIELD_deciderResult
        FD_ISEDITABLE,    // FIELD_blerTh
        FD_ISEDITABLE,    // FIELD_blerValue
        FD_ISEDITABLE,    // FIELD_txMode
        FD_ISEDITABLE,    // FIELD_frameType
        FD_ISEDITABLE,    // FIELD_txPower
        FD_ISEDITABLE,    // FIELD_d2dTxPower
        FD_ISEDITABLE,    // FIELD_totalGrantedBlocks
        FD_ISEDITABLE,    // FIELD_grantId
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_userTxParams
        0,    // FIELD_grantedBlocks
        FD_ISCOMPOUND,    // FIELD_coord
        FD_ISCOMPOUND,    // FIELD_feedbackReq
    };
    return (field >= 0 && field < 21) ? fieldTypeFlags[field] : 0;
}

const char *UserControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isNr",
        "carrierFrequency",
        "acid",
        "cw",
        "txNumber",
        "ndi",
        "isCorruptible",
        "isBroadcast",
        "deciderResult",
        "blerTh",
        "blerValue",
        "txMode",
        "frameType",
        "txPower",
        "d2dTxPower",
        "totalGrantedBlocks",
        "grantId",
        "userTxParams",
        "grantedBlocks",
        "coord",
        "feedbackReq",
    };
    return (field >= 0 && field < 21) ? fieldNames[field] : nullptr;
}

int UserControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "isNr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "carrierFrequency") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "acid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "cw") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "txNumber") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "ndi") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isCorruptible") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "isBroadcast") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "deciderResult") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "blerTh") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "blerValue") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "txMode") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "frameType") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "txPower") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "d2dTxPower") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "totalGrantedBlocks") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "grantId") == 0) return baseIndex + 16;
    if (strcmp(fieldName, "userTxParams") == 0) return baseIndex + 17;
    if (strcmp(fieldName, "grantedBlocks") == 0) return baseIndex + 18;
    if (strcmp(fieldName, "coord") == 0) return baseIndex + 19;
    if (strcmp(fieldName, "feedbackReq") == 0) return baseIndex + 20;
    return base ? base->findField(fieldName) : -1;
}

const char *UserControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isNr
        "inet::GHz",    // FIELD_carrierFrequency
        "unsigned char",    // FIELD_acid
        "unsigned char",    // FIELD_cw
        "unsigned char",    // FIELD_txNumber
        "bool",    // FIELD_ndi
        "bool",    // FIELD_isCorruptible
        "bool",    // FIELD_isBroadcast
        "bool",    // FIELD_deciderResult
        "double",    // FIELD_blerTh
        "double",    // FIELD_blerValue
        "unsigned short",    // FIELD_txMode
        "unsigned int",    // FIELD_frameType
        "double",    // FIELD_txPower
        "double",    // FIELD_d2dTxPower
        "unsigned int",    // FIELD_totalGrantedBlocks
        "unsigned int",    // FIELD_grantId
        "simu5g::UserTxParams",    // FIELD_userTxParams
        "simu5g::RbMap",    // FIELD_grantedBlocks
        "inet::Coord",    // FIELD_coord
        "simu5g::FeedbackRequest",    // FIELD_feedbackReq
    };
    return (field >= 0 && field < 21) ? fieldTypeStrings[field] : nullptr;
}

const char **UserControlInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_txMode: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_frameType: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        case FIELD_userTxParams: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *UserControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_txMode:
            if (!strcmp(propertyName, "enum")) return "TxMode";
            if (!strcmp(propertyName, "enum")) return "simu5g::TxMode";
            return nullptr;
        case FIELD_frameType:
            if (!strcmp(propertyName, "enum")) return "LtePhyFrameType";
            if (!strcmp(propertyName, "enum")) return "simu5g::LtePhyFrameType";
            return nullptr;
        case FIELD_userTxParams:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int UserControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UserControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UserControlInfo'", field);
    }
}

const char *UserControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_userTxParams: { const UserTxParams * value = pp->getUserTxParams(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string UserControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_isNr: return bool2string(pp->isNr());
        case FIELD_carrierFrequency: return inet::unit2string(pp->getCarrierFrequency());
        case FIELD_acid: return ulong2string(pp->getAcid());
        case FIELD_cw: return ulong2string(pp->getCw());
        case FIELD_txNumber: return ulong2string(pp->getTxNumber());
        case FIELD_ndi: return bool2string(pp->getNdi());
        case FIELD_isCorruptible: return bool2string(pp->isCorruptible());
        case FIELD_isBroadcast: return bool2string(pp->isBroadcast());
        case FIELD_deciderResult: return bool2string(pp->getDeciderResult());
        case FIELD_blerTh: return double2string(pp->getBlerTh());
        case FIELD_blerValue: return double2string(pp->getBlerValue());
        case FIELD_txMode: return enum2string(pp->getTxMode(), "simu5g::TxMode");
        case FIELD_frameType: return enum2string(pp->getFrameType(), "simu5g::LtePhyFrameType");
        case FIELD_txPower: return double2string(pp->getTxPower());
        case FIELD_d2dTxPower: return double2string(pp->getD2dTxPower());
        case FIELD_totalGrantedBlocks: return ulong2string(pp->getTotalGrantedBlocks());
        case FIELD_grantId: return ulong2string(pp->getGrantId());
        case FIELD_userTxParams: return "";
        case FIELD_grantedBlocks: return "";
        case FIELD_coord: return pp->getCoord().str();
        case FIELD_feedbackReq: return "";
        default: return "";
    }
}

void UserControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_isNr: pp->setIsNr(string2bool(value)); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(inet::GHz(string2double(value))); break;
        case FIELD_acid: pp->setAcid(string2ulong(value)); break;
        case FIELD_cw: pp->setCw(string2ulong(value)); break;
        case FIELD_txNumber: pp->setTxNumber(string2ulong(value)); break;
        case FIELD_ndi: pp->setNdi(string2bool(value)); break;
        case FIELD_isCorruptible: pp->setIsCorruptible(string2bool(value)); break;
        case FIELD_isBroadcast: pp->setIsBroadcast(string2bool(value)); break;
        case FIELD_deciderResult: pp->setDeciderResult(string2bool(value)); break;
        case FIELD_blerTh: pp->setBlerTh(string2double(value)); break;
        case FIELD_blerValue: pp->setBlerValue(string2double(value)); break;
        case FIELD_txMode: pp->setTxMode((simu5g::TxMode)string2enum(value, "simu5g::TxMode")); break;
        case FIELD_frameType: pp->setFrameType((simu5g::LtePhyFrameType)string2enum(value, "simu5g::LtePhyFrameType")); break;
        case FIELD_txPower: pp->setTxPower(string2double(value)); break;
        case FIELD_d2dTxPower: pp->setD2dTxPower(string2double(value)); break;
        case FIELD_totalGrantedBlocks: pp->setTotalGrantedBlocks(string2ulong(value)); break;
        case FIELD_grantId: pp->setGrantId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserControlInfo'", field);
    }
}

omnetpp::cValue UserControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_isNr: return pp->isNr();
        case FIELD_carrierFrequency: return cValue(pp->getCarrierFrequency().get(),"GHz");
        case FIELD_acid: return (omnetpp::intval_t)(pp->getAcid());
        case FIELD_cw: return (omnetpp::intval_t)(pp->getCw());
        case FIELD_txNumber: return (omnetpp::intval_t)(pp->getTxNumber());
        case FIELD_ndi: return pp->getNdi();
        case FIELD_isCorruptible: return pp->isCorruptible();
        case FIELD_isBroadcast: return pp->isBroadcast();
        case FIELD_deciderResult: return pp->getDeciderResult();
        case FIELD_blerTh: return pp->getBlerTh();
        case FIELD_blerValue: return pp->getBlerValue();
        case FIELD_txMode: return (omnetpp::intval_t)(pp->getTxMode());
        case FIELD_frameType: return (omnetpp::intval_t)(pp->getFrameType());
        case FIELD_txPower: return pp->getTxPower();
        case FIELD_d2dTxPower: return pp->getD2dTxPower();
        case FIELD_totalGrantedBlocks: return (omnetpp::intval_t)(pp->getTotalGrantedBlocks());
        case FIELD_grantId: return (omnetpp::intval_t)(pp->getGrantId());
        case FIELD_userTxParams: return omnetpp::toAnyPtr(pp->getUserTxParams()); break;
        case FIELD_grantedBlocks: return omnetpp::toAnyPtr(&pp->getGrantedBlocks()); break;
        case FIELD_coord: return omnetpp::toAnyPtr(&pp->getCoord()); break;
        case FIELD_feedbackReq: return omnetpp::toAnyPtr(&pp->getFeedbackReq()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UserControlInfo' as cValue -- field index out of range?", field);
    }
}

void UserControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_isNr: pp->setIsNr(value.boolValue()); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(inet::GHz(value.doubleValueInUnit("GHz"))); break;
        case FIELD_acid: pp->setAcid(omnetpp::checked_int_cast<unsigned char>(value.intValue())); break;
        case FIELD_cw: pp->setCw(omnetpp::checked_int_cast<unsigned char>(value.intValue())); break;
        case FIELD_txNumber: pp->setTxNumber(omnetpp::checked_int_cast<unsigned char>(value.intValue())); break;
        case FIELD_ndi: pp->setNdi(value.boolValue()); break;
        case FIELD_isCorruptible: pp->setIsCorruptible(value.boolValue()); break;
        case FIELD_isBroadcast: pp->setIsBroadcast(value.boolValue()); break;
        case FIELD_deciderResult: pp->setDeciderResult(value.boolValue()); break;
        case FIELD_blerTh: pp->setBlerTh(value.doubleValue()); break;
        case FIELD_blerValue: pp->setBlerValue(value.doubleValue()); break;
        case FIELD_txMode: pp->setTxMode((simu5g::TxMode)value.intValue()); break;
        case FIELD_frameType: pp->setFrameType((simu5g::LtePhyFrameType)value.intValue()); break;
        case FIELD_txPower: pp->setTxPower(value.doubleValue()); break;
        case FIELD_d2dTxPower: pp->setD2dTxPower(value.doubleValue()); break;
        case FIELD_totalGrantedBlocks: pp->setTotalGrantedBlocks(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_grantId: pp->setGrantId(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_userTxParams: pp->setUserTxParams(omnetpp::fromAnyPtr<UserTxParams>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserControlInfo'", field);
    }
}

const char *UserControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_userTxParams: return omnetpp::opp_typename(typeid(UserTxParams));
        case FIELD_coord: return omnetpp::opp_typename(typeid(::inet::Coord));
        case FIELD_feedbackReq: return omnetpp::opp_typename(typeid(FeedbackRequest));
        default: return nullptr;
    };
}

omnetpp::any_ptr UserControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_userTxParams: return omnetpp::toAnyPtr(pp->getUserTxParams()); break;
        case FIELD_grantedBlocks: return omnetpp::toAnyPtr(&pp->getGrantedBlocks()); break;
        case FIELD_coord: return omnetpp::toAnyPtr(&pp->getCoord()); break;
        case FIELD_feedbackReq: return omnetpp::toAnyPtr(&pp->getFeedbackReq()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UserControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UserControlInfo *pp = omnetpp::fromAnyPtr<UserControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_userTxParams: pp->setUserTxParams(omnetpp::fromAnyPtr<UserTxParams>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserControlInfo'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

