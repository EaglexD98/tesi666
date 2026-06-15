//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/common/LteCommon.msg.
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
#include "LteCommon_m.h"

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

RemoteUnitPhyData::RemoteUnitPhyData()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RemoteUnitPhyData& a)
{
    doParsimPacking(b,a.txPower);
    doParsimPacking(b,a.m);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RemoteUnitPhyData& a)
{
    doParsimUnpacking(b,a.txPower);
    doParsimUnpacking(b,a.m);
}

class RemoteUnitPhyDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_txPower,
        FIELD_m,
    };
  public:
    RemoteUnitPhyDataDescriptor();
    virtual ~RemoteUnitPhyDataDescriptor();

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

Register_ClassDescriptor(RemoteUnitPhyDataDescriptor)

RemoteUnitPhyDataDescriptor::RemoteUnitPhyDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::RemoteUnitPhyData)), "")
{
    propertyNames = nullptr;
}

RemoteUnitPhyDataDescriptor::~RemoteUnitPhyDataDescriptor()
{
    delete[] propertyNames;
}

bool RemoteUnitPhyDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RemoteUnitPhyData *>(obj)!=nullptr;
}

const char **RemoteUnitPhyDataDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RemoteUnitPhyDataDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RemoteUnitPhyDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RemoteUnitPhyDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_txPower
        FD_ISCOMPOUND,    // FIELD_m
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RemoteUnitPhyDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "txPower",
        "m",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RemoteUnitPhyDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "txPower") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "m") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RemoteUnitPhyDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_txPower
        "inet::Coord",    // FIELD_m
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RemoteUnitPhyDataDescriptor::getFieldPropertyNames(int field) const
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

const char *RemoteUnitPhyDataDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RemoteUnitPhyDataDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RemoteUnitPhyDataDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RemoteUnitPhyData'", field);
    }
}

const char *RemoteUnitPhyDataDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RemoteUnitPhyDataDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        case FIELD_txPower: return long2string(pp->txPower);
        case FIELD_m: return pp->m.str();
        default: return "";
    }
}

void RemoteUnitPhyDataDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        case FIELD_txPower: pp->txPower = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoteUnitPhyData'", field);
    }
}

omnetpp::cValue RemoteUnitPhyDataDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        case FIELD_txPower: return pp->txPower;
        case FIELD_m: return omnetpp::toAnyPtr(&pp->m); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RemoteUnitPhyData' as cValue -- field index out of range?", field);
    }
}

void RemoteUnitPhyDataDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        case FIELD_txPower: pp->txPower = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoteUnitPhyData'", field);
    }
}

const char *RemoteUnitPhyDataDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_m: return omnetpp::opp_typename(typeid(::inet::Coord));
        default: return nullptr;
    };
}

omnetpp::any_ptr RemoteUnitPhyDataDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        case FIELD_m: return omnetpp::toAnyPtr(&pp->m); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RemoteUnitPhyDataDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RemoteUnitPhyData *pp = omnetpp::fromAnyPtr<RemoteUnitPhyData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RemoteUnitPhyData'", field);
    }
}

FeedbackRequest::FeedbackRequest()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FeedbackRequest& a)
{
    doParsimPacking(b,a.request);
    doParsimPacking(b,a.genType);
    doParsimPacking(b,a.type);
    doParsimPacking(b,a.txMode);
    doParsimPacking(b,a.dasAware);
    doParsimPacking(b,a.rbAllocationType);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FeedbackRequest& a)
{
    doParsimUnpacking(b,a.request);
    doParsimUnpacking(b,a.genType);
    doParsimUnpacking(b,a.type);
    doParsimUnpacking(b,a.txMode);
    doParsimUnpacking(b,a.dasAware);
    doParsimUnpacking(b,a.rbAllocationType);
}

class FeedbackRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_request,
        FIELD_genType,
        FIELD_type,
        FIELD_txMode,
        FIELD_dasAware,
        FIELD_rbAllocationType,
    };
  public:
    FeedbackRequestDescriptor();
    virtual ~FeedbackRequestDescriptor();

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

Register_ClassDescriptor(FeedbackRequestDescriptor)

FeedbackRequestDescriptor::FeedbackRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::FeedbackRequest)), "")
{
    propertyNames = nullptr;
}

FeedbackRequestDescriptor::~FeedbackRequestDescriptor()
{
    delete[] propertyNames;
}

bool FeedbackRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FeedbackRequest *>(obj)!=nullptr;
}

const char **FeedbackRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FeedbackRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FeedbackRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int FeedbackRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_request
        0,    // FIELD_genType
        0,    // FIELD_type
        0,    // FIELD_txMode
        FD_ISEDITABLE,    // FIELD_dasAware
        0,    // FIELD_rbAllocationType
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *FeedbackRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "request",
        "genType",
        "type",
        "txMode",
        "dasAware",
        "rbAllocationType",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int FeedbackRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "request") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "genType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "txMode") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "dasAware") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "rbAllocationType") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *FeedbackRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_request
        "simu5g::FeedbackGeneratorType",    // FIELD_genType
        "simu5g::FeedbackType",    // FIELD_type
        "simu5g::TxMode",    // FIELD_txMode
        "bool",    // FIELD_dasAware
        "simu5g::RbAllocationType",    // FIELD_rbAllocationType
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **FeedbackRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_genType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_txMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_rbAllocationType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *FeedbackRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_genType:
            if (!strcmp(propertyName, "enum")) return "simu5g::FeedbackGeneratorType";
            return nullptr;
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "simu5g::FeedbackType";
            return nullptr;
        case FIELD_txMode:
            if (!strcmp(propertyName, "enum")) return "simu5g::TxMode";
            return nullptr;
        case FIELD_rbAllocationType:
            if (!strcmp(propertyName, "enum")) return "simu5g::RbAllocationType";
            return nullptr;
        default: return nullptr;
    }
}

int FeedbackRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FeedbackRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FeedbackRequest'", field);
    }
}

const char *FeedbackRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FeedbackRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        case FIELD_request: return bool2string(pp->request);
        case FIELD_genType: return enum2string(pp->genType, "simu5g::FeedbackGeneratorType");
        case FIELD_type: return enum2string(pp->type, "simu5g::FeedbackType");
        case FIELD_txMode: return enum2string(pp->txMode, "simu5g::TxMode");
        case FIELD_dasAware: return bool2string(pp->dasAware);
        case FIELD_rbAllocationType: return enum2string(pp->rbAllocationType, "simu5g::RbAllocationType");
        default: return "";
    }
}

void FeedbackRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->request = string2bool(value); break;
        case FIELD_dasAware: pp->dasAware = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FeedbackRequest'", field);
    }
}

omnetpp::cValue FeedbackRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        case FIELD_request: return pp->request;
        case FIELD_genType: return static_cast<int>(pp->genType);
        case FIELD_type: return static_cast<int>(pp->type);
        case FIELD_txMode: return static_cast<int>(pp->txMode);
        case FIELD_dasAware: return pp->dasAware;
        case FIELD_rbAllocationType: return static_cast<int>(pp->rbAllocationType);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FeedbackRequest' as cValue -- field index out of range?", field);
    }
}

void FeedbackRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->request = value.boolValue(); break;
        case FIELD_dasAware: pp->dasAware = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FeedbackRequest'", field);
    }
}

const char *FeedbackRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr FeedbackRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FeedbackRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FeedbackRequest *pp = omnetpp::fromAnyPtr<FeedbackRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FeedbackRequest'", field);
    }
}

}  // namespace simu5g

namespace inet {

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

