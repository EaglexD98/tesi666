//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/mac/amc/UserTxParams.msg.
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
#include "UserTxParams_m.h"

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

UserTxParams::UserTxParams()
{
}

UserTxParams::UserTxParams(const UserTxParams& other)
{
    copy(other);
}

UserTxParams::~UserTxParams()
{
}

UserTxParams& UserTxParams::operator=(const UserTxParams& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void UserTxParams::copy(const UserTxParams& other)
{
    this->txMode = other.txMode;
    this->ri = other.ri;
    this->pmi = other.pmi;
    this->valid = other.valid;
// cplusplus {{
    cqiVector = other.cqiVector;
    allowedBands_ = other.allowedBands_;
    antennaSet_ = other.antennaSet_;
// }}
}

void UserTxParams::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->txMode);
    doParsimPacking(b,this->ri);
    // field cqiVector is abstract or custom -- please do packing in customized class
    doParsimPacking(b,this->pmi);
    doParsimPacking(b,this->valid);
// cplusplus {{
    doParsimPacking(b, cqiVector);
    doParsimPacking(b, allowedBands_);
    doParsimPacking(b, antennaSet_);
// }}
}

void UserTxParams::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->txMode);
    doParsimUnpacking(b,this->ri);
    // field cqiVector is abstract or custom -- please do unpacking in customized class
    doParsimUnpacking(b,this->pmi);
    doParsimUnpacking(b,this->valid);
// cplusplus {{
    doParsimUnpacking(b, cqiVector);
    doParsimUnpacking(b, allowedBands_);
    doParsimUnpacking(b, antennaSet_);
// }}
}

TxMode UserTxParams::readTxMode() const
{
    return this->txMode;
}

void UserTxParams::writeTxMode(TxMode txMode)
{
    this->txMode = txMode;
}

Rank UserTxParams::readRank() const
{
    return this->ri;
}

void UserTxParams::writeRank(Rank ri)
{
    this->ri = ri;
}

Pmi UserTxParams::readPmi() const
{
    return this->pmi;
}

void UserTxParams::writePmi(Pmi pmi)
{
    this->pmi = pmi;
}

bool UserTxParams::isValid() const
{
    return this->valid;
}

void UserTxParams::setValid(bool valid)
{
    this->valid = valid;
}

class UserTxParamsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_txMode,
        FIELD_ri,
        FIELD_cqiVector,
        FIELD_pmi,
        FIELD_valid,
    };
  public:
    UserTxParamsDescriptor();
    virtual ~UserTxParamsDescriptor();

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

Register_ClassDescriptor(UserTxParamsDescriptor)

UserTxParamsDescriptor::UserTxParamsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::UserTxParams)), "")
{
    propertyNames = nullptr;
}

UserTxParamsDescriptor::~UserTxParamsDescriptor()
{
    delete[] propertyNames;
}

bool UserTxParamsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UserTxParams *>(obj)!=nullptr;
}

const char **UserTxParamsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UserTxParamsDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UserTxParamsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int UserTxParamsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_txMode
        FD_ISEDITABLE,    // FIELD_ri
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_cqiVector
        FD_ISEDITABLE,    // FIELD_pmi
        FD_ISEDITABLE,    // FIELD_valid
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *UserTxParamsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "txMode",
        "ri",
        "cqiVector",
        "pmi",
        "valid",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int UserTxParamsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "txMode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ri") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "cqiVector") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pmi") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "valid") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *UserTxParamsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simu5g::TxMode",    // FIELD_txMode
        "simu5g::Rank",    // FIELD_ri
        "simu5g::Cqi",    // FIELD_cqiVector
        "simu5g::Pmi",    // FIELD_pmi
        "bool",    // FIELD_valid
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **UserTxParamsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_txMode: {
            static const char *names[] = { "getter", "setter", "enum",  nullptr };
            return names;
        }
        case FIELD_ri: {
            static const char *names[] = { "getter", "setter",  nullptr };
            return names;
        }
        case FIELD_cqiVector: {
            static const char *names[] = { "custom",  nullptr };
            return names;
        }
        case FIELD_pmi: {
            static const char *names[] = { "getter", "setter",  nullptr };
            return names;
        }
        case FIELD_valid: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *UserTxParamsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_txMode:
            if (!strcmp(propertyName, "getter")) return "readTxMode";
            if (!strcmp(propertyName, "setter")) return "writeTxMode";
            if (!strcmp(propertyName, "enum")) return "simu5g::TxMode";
            return nullptr;
        case FIELD_ri:
            if (!strcmp(propertyName, "getter")) return "readRank";
            if (!strcmp(propertyName, "setter")) return "writeRank";
            return nullptr;
        case FIELD_cqiVector:
            if (!strcmp(propertyName, "custom")) return "";
            return nullptr;
        case FIELD_pmi:
            if (!strcmp(propertyName, "getter")) return "readPmi";
            if (!strcmp(propertyName, "setter")) return "writePmi";
            return nullptr;
        case FIELD_valid:
            if (!strcmp(propertyName, "getter")) return "isValid";
            return nullptr;
        default: return nullptr;
    }
}

int UserTxParamsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_cqiVector: return pp->getCqiVectorArraySize();
        default: return 0;
    }
}

void UserTxParamsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_cqiVector: pp->setCqiVectorArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UserTxParams'", field);
    }
}

const char *UserTxParamsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UserTxParamsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_txMode: return enum2string(pp->readTxMode(), "simu5g::TxMode");
        case FIELD_ri: return int642string(pp->readRank());
        case FIELD_cqiVector: return int642string(pp->getCqiVector(i));
        case FIELD_pmi: return int642string(pp->readPmi());
        case FIELD_valid: return bool2string(pp->isValid());
        default: return "";
    }
}

void UserTxParamsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_ri: pp->writeRank(string2int64(value)); break;
        case FIELD_cqiVector: pp->setCqiVector(i,string2int64(value)); break;
        case FIELD_pmi: pp->writePmi(string2int64(value)); break;
        case FIELD_valid: pp->setValid(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserTxParams'", field);
    }
}

omnetpp::cValue UserTxParamsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_txMode: return static_cast<int>(pp->readTxMode());
        case FIELD_ri: return (omnetpp::intval_t)(pp->readRank());
        case FIELD_cqiVector: return (omnetpp::intval_t)(pp->getCqiVector(i));
        case FIELD_pmi: return (omnetpp::intval_t)(pp->readPmi());
        case FIELD_valid: return pp->isValid();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UserTxParams' as cValue -- field index out of range?", field);
    }
}

void UserTxParamsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        case FIELD_ri: pp->writeRank(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_cqiVector: pp->setCqiVector(i,omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_pmi: pp->writePmi(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_valid: pp->setValid(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserTxParams'", field);
    }
}

const char *UserTxParamsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr UserTxParamsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UserTxParamsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UserTxParams *pp = omnetpp::fromAnyPtr<UserTxParams>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UserTxParams'", field);
    }
}

// cplusplus {{
std::vector<Cqi> UserTxParams::CQI_INIT_VALUES = { NOSIGNALCQI };
// }}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

