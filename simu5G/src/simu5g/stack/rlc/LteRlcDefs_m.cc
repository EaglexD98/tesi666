//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/rlc/LteRlcDefs.msg.
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
#include "LteRlcDefs_m.h"

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

Register_Enum(simu5g::LteAmType, (simu5g::LteAmType::DATA, simu5g::LteAmType::ACK, simu5g::LteAmType::MRW, simu5g::LteAmType::MRW_ACK));

RlcFragDesc::RlcFragDesc()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RlcFragDesc& a)
{
    doParsimPacking(b,a.sduSize_);
    doParsimPacking(b,a.fragUnit_);
    doParsimPacking(b,a.totalFragments_);
    doParsimPacking(b,a.fragCounter_);
    doParsimPacking(b,a.firstSn_);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RlcFragDesc& a)
{
    doParsimUnpacking(b,a.sduSize_);
    doParsimUnpacking(b,a.fragUnit_);
    doParsimUnpacking(b,a.totalFragments_);
    doParsimUnpacking(b,a.fragCounter_);
    doParsimUnpacking(b,a.firstSn_);
}

class RlcFragDescDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sduSize_,
        FIELD_fragUnit_,
        FIELD_totalFragments_,
        FIELD_fragCounter_,
        FIELD_firstSn_,
    };
  public:
    RlcFragDescDescriptor();
    virtual ~RlcFragDescDescriptor();

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

Register_ClassDescriptor(RlcFragDescDescriptor)

RlcFragDescDescriptor::RlcFragDescDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::RlcFragDesc)), "")
{
    propertyNames = nullptr;
}

RlcFragDescDescriptor::~RlcFragDescDescriptor()
{
    delete[] propertyNames;
}

bool RlcFragDescDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RlcFragDesc *>(obj)!=nullptr;
}

const char **RlcFragDescDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RlcFragDescDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RlcFragDescDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RlcFragDescDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sduSize_
        FD_ISEDITABLE,    // FIELD_fragUnit_
        FD_ISEDITABLE,    // FIELD_totalFragments_
        FD_ISEDITABLE,    // FIELD_fragCounter_
        FD_ISEDITABLE,    // FIELD_firstSn_
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RlcFragDescDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sduSize_",
        "fragUnit_",
        "totalFragments_",
        "fragCounter_",
        "firstSn_",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RlcFragDescDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sduSize_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fragUnit_") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "totalFragments_") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "fragCounter_") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "firstSn_") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RlcFragDescDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sduSize_
        "int",    // FIELD_fragUnit_
        "int",    // FIELD_totalFragments_
        "int",    // FIELD_fragCounter_
        "int",    // FIELD_firstSn_
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RlcFragDescDescriptor::getFieldPropertyNames(int field) const
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

const char *RlcFragDescDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RlcFragDescDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RlcFragDescDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RlcFragDesc'", field);
    }
}

const char *RlcFragDescDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RlcFragDescDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        case FIELD_sduSize_: return long2string(pp->sduSize_);
        case FIELD_fragUnit_: return long2string(pp->fragUnit_);
        case FIELD_totalFragments_: return long2string(pp->totalFragments_);
        case FIELD_fragCounter_: return long2string(pp->fragCounter_);
        case FIELD_firstSn_: return long2string(pp->firstSn_);
        default: return "";
    }
}

void RlcFragDescDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        case FIELD_sduSize_: pp->sduSize_ = string2long(value); break;
        case FIELD_fragUnit_: pp->fragUnit_ = string2long(value); break;
        case FIELD_totalFragments_: pp->totalFragments_ = string2long(value); break;
        case FIELD_fragCounter_: pp->fragCounter_ = string2long(value); break;
        case FIELD_firstSn_: pp->firstSn_ = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcFragDesc'", field);
    }
}

omnetpp::cValue RlcFragDescDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        case FIELD_sduSize_: return pp->sduSize_;
        case FIELD_fragUnit_: return pp->fragUnit_;
        case FIELD_totalFragments_: return pp->totalFragments_;
        case FIELD_fragCounter_: return pp->fragCounter_;
        case FIELD_firstSn_: return pp->firstSn_;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RlcFragDesc' as cValue -- field index out of range?", field);
    }
}

void RlcFragDescDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        case FIELD_sduSize_: pp->sduSize_ = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_fragUnit_: pp->fragUnit_ = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_totalFragments_: pp->totalFragments_ = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_fragCounter_: pp->fragCounter_ = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_firstSn_: pp->firstSn_ = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcFragDesc'", field);
    }
}

const char *RlcFragDescDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RlcFragDescDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RlcFragDescDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcFragDesc *pp = omnetpp::fromAnyPtr<RlcFragDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcFragDesc'", field);
    }
}

RlcWindowDesc::RlcWindowDesc()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RlcWindowDesc& a)
{
    doParsimPacking(b,a.firstSeqNum_);
    doParsimPacking(b,a.seqNum_);
    doParsimPacking(b,a.windowSize_);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RlcWindowDesc& a)
{
    doParsimUnpacking(b,a.firstSeqNum_);
    doParsimUnpacking(b,a.seqNum_);
    doParsimUnpacking(b,a.windowSize_);
}

class RlcWindowDescDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_firstSeqNum_,
        FIELD_seqNum_,
        FIELD_windowSize_,
    };
  public:
    RlcWindowDescDescriptor();
    virtual ~RlcWindowDescDescriptor();

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

Register_ClassDescriptor(RlcWindowDescDescriptor)

RlcWindowDescDescriptor::RlcWindowDescDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::RlcWindowDesc)), "")
{
    propertyNames = nullptr;
}

RlcWindowDescDescriptor::~RlcWindowDescDescriptor()
{
    delete[] propertyNames;
}

bool RlcWindowDescDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RlcWindowDesc *>(obj)!=nullptr;
}

const char **RlcWindowDescDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RlcWindowDescDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RlcWindowDescDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RlcWindowDescDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_firstSeqNum_
        FD_ISEDITABLE,    // FIELD_seqNum_
        FD_ISEDITABLE,    // FIELD_windowSize_
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RlcWindowDescDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "firstSeqNum_",
        "seqNum_",
        "windowSize_",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RlcWindowDescDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "firstSeqNum_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "seqNum_") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "windowSize_") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RlcWindowDescDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_firstSeqNum_
        "unsigned int",    // FIELD_seqNum_
        "unsigned int",    // FIELD_windowSize_
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RlcWindowDescDescriptor::getFieldPropertyNames(int field) const
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

const char *RlcWindowDescDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RlcWindowDescDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RlcWindowDescDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RlcWindowDesc'", field);
    }
}

const char *RlcWindowDescDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RlcWindowDescDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSeqNum_: return ulong2string(pp->firstSeqNum_);
        case FIELD_seqNum_: return ulong2string(pp->seqNum_);
        case FIELD_windowSize_: return ulong2string(pp->windowSize_);
        default: return "";
    }
}

void RlcWindowDescDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSeqNum_: pp->firstSeqNum_ = string2ulong(value); break;
        case FIELD_seqNum_: pp->seqNum_ = string2ulong(value); break;
        case FIELD_windowSize_: pp->windowSize_ = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcWindowDesc'", field);
    }
}

omnetpp::cValue RlcWindowDescDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSeqNum_: return (omnetpp::intval_t)(pp->firstSeqNum_);
        case FIELD_seqNum_: return (omnetpp::intval_t)(pp->seqNum_);
        case FIELD_windowSize_: return (omnetpp::intval_t)(pp->windowSize_);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RlcWindowDesc' as cValue -- field index out of range?", field);
    }
}

void RlcWindowDescDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSeqNum_: pp->firstSeqNum_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_seqNum_: pp->seqNum_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_windowSize_: pp->windowSize_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcWindowDesc'", field);
    }
}

const char *RlcWindowDescDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RlcWindowDescDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RlcWindowDescDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcWindowDesc *pp = omnetpp::fromAnyPtr<RlcWindowDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcWindowDesc'", field);
    }
}

MrwDesc::MrwDesc()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const MrwDesc& a)
{
    doParsimPacking(b,a.mrwSeqNum_);
    doParsimPacking(b,a.lastMrw_);
}

void __doUnpacking(omnetpp::cCommBuffer *b, MrwDesc& a)
{
    doParsimUnpacking(b,a.mrwSeqNum_);
    doParsimUnpacking(b,a.lastMrw_);
}

class MrwDescDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_mrwSeqNum_,
        FIELD_lastMrw_,
    };
  public:
    MrwDescDescriptor();
    virtual ~MrwDescDescriptor();

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

Register_ClassDescriptor(MrwDescDescriptor)

MrwDescDescriptor::MrwDescDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::MrwDesc)), "")
{
    propertyNames = nullptr;
}

MrwDescDescriptor::~MrwDescDescriptor()
{
    delete[] propertyNames;
}

bool MrwDescDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MrwDesc *>(obj)!=nullptr;
}

const char **MrwDescDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MrwDescDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MrwDescDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int MrwDescDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_mrwSeqNum_
        FD_ISEDITABLE,    // FIELD_lastMrw_
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *MrwDescDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "mrwSeqNum_",
        "lastMrw_",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int MrwDescDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "mrwSeqNum_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lastMrw_") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *MrwDescDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_mrwSeqNum_
        "unsigned int",    // FIELD_lastMrw_
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **MrwDescDescriptor::getFieldPropertyNames(int field) const
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

const char *MrwDescDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int MrwDescDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MrwDescDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MrwDesc'", field);
    }
}

const char *MrwDescDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MrwDescDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        case FIELD_mrwSeqNum_: return ulong2string(pp->mrwSeqNum_);
        case FIELD_lastMrw_: return ulong2string(pp->lastMrw_);
        default: return "";
    }
}

void MrwDescDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        case FIELD_mrwSeqNum_: pp->mrwSeqNum_ = string2ulong(value); break;
        case FIELD_lastMrw_: pp->lastMrw_ = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MrwDesc'", field);
    }
}

omnetpp::cValue MrwDescDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        case FIELD_mrwSeqNum_: return (omnetpp::intval_t)(pp->mrwSeqNum_);
        case FIELD_lastMrw_: return (omnetpp::intval_t)(pp->lastMrw_);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MrwDesc' as cValue -- field index out of range?", field);
    }
}

void MrwDescDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        case FIELD_mrwSeqNum_: pp->mrwSeqNum_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_lastMrw_: pp->lastMrw_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MrwDesc'", field);
    }
}

const char *MrwDescDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr MrwDescDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MrwDescDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MrwDesc *pp = omnetpp::fromAnyPtr<MrwDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MrwDesc'", field);
    }
}

Register_Enum(simu5g::RlcAmTimerType, (simu5g::RlcAmTimerType::PDU_T, simu5g::RlcAmTimerType::MRW_T, simu5g::RlcAmTimerType::BUFFER_T, simu5g::RlcAmTimerType::BUFFERSTATUS_T));

FramingInfo::FramingInfo()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FramingInfo& a)
{
    doParsimPacking(b,a.firstIsFragment);
    doParsimPacking(b,a.lastIsFragment);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FramingInfo& a)
{
    doParsimUnpacking(b,a.firstIsFragment);
    doParsimUnpacking(b,a.lastIsFragment);
}

class FramingInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_firstIsFragment,
        FIELD_lastIsFragment,
    };
  public:
    FramingInfoDescriptor();
    virtual ~FramingInfoDescriptor();

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

Register_ClassDescriptor(FramingInfoDescriptor)

FramingInfoDescriptor::FramingInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::FramingInfo)), "")
{
    propertyNames = nullptr;
}

FramingInfoDescriptor::~FramingInfoDescriptor()
{
    delete[] propertyNames;
}

bool FramingInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FramingInfo *>(obj)!=nullptr;
}

const char **FramingInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FramingInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FramingInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int FramingInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_firstIsFragment
        FD_ISEDITABLE,    // FIELD_lastIsFragment
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *FramingInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "firstIsFragment",
        "lastIsFragment",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int FramingInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "firstIsFragment") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lastIsFragment") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *FramingInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_firstIsFragment
        "bool",    // FIELD_lastIsFragment
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **FramingInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *FramingInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FramingInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FramingInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FramingInfo'", field);
    }
}

const char *FramingInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FramingInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        case FIELD_firstIsFragment: return bool2string(pp->firstIsFragment);
        case FIELD_lastIsFragment: return bool2string(pp->lastIsFragment);
        default: return "";
    }
}

void FramingInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        case FIELD_firstIsFragment: pp->firstIsFragment = string2bool(value); break;
        case FIELD_lastIsFragment: pp->lastIsFragment = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FramingInfo'", field);
    }
}

omnetpp::cValue FramingInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        case FIELD_firstIsFragment: return pp->firstIsFragment;
        case FIELD_lastIsFragment: return pp->lastIsFragment;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FramingInfo' as cValue -- field index out of range?", field);
    }
}

void FramingInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        case FIELD_firstIsFragment: pp->firstIsFragment = value.boolValue(); break;
        case FIELD_lastIsFragment: pp->lastIsFragment = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FramingInfo'", field);
    }
}

const char *FramingInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr FramingInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FramingInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FramingInfo *pp = omnetpp::fromAnyPtr<FramingInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FramingInfo'", field);
    }
}

RlcUmRxWindowDesc::RlcUmRxWindowDesc()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RlcUmRxWindowDesc& a)
{
    doParsimPacking(b,a.firstSno_);
    doParsimPacking(b,a.firstSnoForReordering_);
    doParsimPacking(b,a.reorderingSno_);
    doParsimPacking(b,a.highestReceivedSno_);
    doParsimPacking(b,a.windowSize_);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RlcUmRxWindowDesc& a)
{
    doParsimUnpacking(b,a.firstSno_);
    doParsimUnpacking(b,a.firstSnoForReordering_);
    doParsimUnpacking(b,a.reorderingSno_);
    doParsimUnpacking(b,a.highestReceivedSno_);
    doParsimUnpacking(b,a.windowSize_);
}

class RlcUmRxWindowDescDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_firstSno_,
        FIELD_firstSnoForReordering_,
        FIELD_reorderingSno_,
        FIELD_highestReceivedSno_,
        FIELD_windowSize_,
    };
  public:
    RlcUmRxWindowDescDescriptor();
    virtual ~RlcUmRxWindowDescDescriptor();

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

Register_ClassDescriptor(RlcUmRxWindowDescDescriptor)

RlcUmRxWindowDescDescriptor::RlcUmRxWindowDescDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::RlcUmRxWindowDesc)), "")
{
    propertyNames = nullptr;
}

RlcUmRxWindowDescDescriptor::~RlcUmRxWindowDescDescriptor()
{
    delete[] propertyNames;
}

bool RlcUmRxWindowDescDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RlcUmRxWindowDesc *>(obj)!=nullptr;
}

const char **RlcUmRxWindowDescDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RlcUmRxWindowDescDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RlcUmRxWindowDescDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RlcUmRxWindowDescDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_firstSno_
        FD_ISEDITABLE,    // FIELD_firstSnoForReordering_
        FD_ISEDITABLE,    // FIELD_reorderingSno_
        FD_ISEDITABLE,    // FIELD_highestReceivedSno_
        FD_ISEDITABLE,    // FIELD_windowSize_
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RlcUmRxWindowDescDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "firstSno_",
        "firstSnoForReordering_",
        "reorderingSno_",
        "highestReceivedSno_",
        "windowSize_",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RlcUmRxWindowDescDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "firstSno_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "firstSnoForReordering_") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reorderingSno_") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "highestReceivedSno_") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "windowSize_") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RlcUmRxWindowDescDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_firstSno_
        "unsigned int",    // FIELD_firstSnoForReordering_
        "unsigned int",    // FIELD_reorderingSno_
        "unsigned int",    // FIELD_highestReceivedSno_
        "unsigned int",    // FIELD_windowSize_
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RlcUmRxWindowDescDescriptor::getFieldPropertyNames(int field) const
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

const char *RlcUmRxWindowDescDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RlcUmRxWindowDescDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RlcUmRxWindowDescDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RlcUmRxWindowDesc'", field);
    }
}

const char *RlcUmRxWindowDescDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RlcUmRxWindowDescDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSno_: return ulong2string(pp->firstSno_);
        case FIELD_firstSnoForReordering_: return ulong2string(pp->firstSnoForReordering_);
        case FIELD_reorderingSno_: return ulong2string(pp->reorderingSno_);
        case FIELD_highestReceivedSno_: return ulong2string(pp->highestReceivedSno_);
        case FIELD_windowSize_: return ulong2string(pp->windowSize_);
        default: return "";
    }
}

void RlcUmRxWindowDescDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSno_: pp->firstSno_ = string2ulong(value); break;
        case FIELD_firstSnoForReordering_: pp->firstSnoForReordering_ = string2ulong(value); break;
        case FIELD_reorderingSno_: pp->reorderingSno_ = string2ulong(value); break;
        case FIELD_highestReceivedSno_: pp->highestReceivedSno_ = string2ulong(value); break;
        case FIELD_windowSize_: pp->windowSize_ = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcUmRxWindowDesc'", field);
    }
}

omnetpp::cValue RlcUmRxWindowDescDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSno_: return (omnetpp::intval_t)(pp->firstSno_);
        case FIELD_firstSnoForReordering_: return (omnetpp::intval_t)(pp->firstSnoForReordering_);
        case FIELD_reorderingSno_: return (omnetpp::intval_t)(pp->reorderingSno_);
        case FIELD_highestReceivedSno_: return (omnetpp::intval_t)(pp->highestReceivedSno_);
        case FIELD_windowSize_: return (omnetpp::intval_t)(pp->windowSize_);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RlcUmRxWindowDesc' as cValue -- field index out of range?", field);
    }
}

void RlcUmRxWindowDescDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        case FIELD_firstSno_: pp->firstSno_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_firstSnoForReordering_: pp->firstSnoForReordering_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_reorderingSno_: pp->reorderingSno_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_highestReceivedSno_: pp->highestReceivedSno_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_windowSize_: pp->windowSize_ = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcUmRxWindowDesc'", field);
    }
}

const char *RlcUmRxWindowDescDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RlcUmRxWindowDescDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RlcUmRxWindowDescDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RlcUmRxWindowDesc *pp = omnetpp::fromAnyPtr<RlcUmRxWindowDesc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RlcUmRxWindowDesc'", field);
    }
}

Register_Enum(simu5g::RlcUmTimerType, (simu5g::RlcUmTimerType::REORDERING_T));

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

