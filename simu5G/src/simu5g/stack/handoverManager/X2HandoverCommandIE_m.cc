//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/handoverManager/X2HandoverCommandIE.msg.
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
#include "X2HandoverCommandIE_m.h"

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

Register_Class(X2HandoverCommandIE)

X2HandoverCommandIE::X2HandoverCommandIE() : ::simu5g::X2InformationElement()
{
    this->setType(X2_HANDOVER_CMD_IE);
    this->setLength(sizeof(MacNodeId) + sizeof(uint8_t));

}

X2HandoverCommandIE::X2HandoverCommandIE(const X2HandoverCommandIE& other) : ::simu5g::X2InformationElement(other)
{
    copy(other);
}

X2HandoverCommandIE::~X2HandoverCommandIE()
{
}

X2HandoverCommandIE& X2HandoverCommandIE::operator=(const X2HandoverCommandIE& other)
{
    if (this == &other) return *this;
    ::simu5g::X2InformationElement::operator=(other);
    copy(other);
    return *this;
}

void X2HandoverCommandIE::copy(const X2HandoverCommandIE& other)
{
    this->startHandover = other.startHandover;
    this->ueId = other.ueId;
}

void X2HandoverCommandIE::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::X2InformationElement::parsimPack(b);
    doParsimPacking(b,this->startHandover);
    doParsimPacking(b,this->ueId);
}

void X2HandoverCommandIE::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::X2InformationElement::parsimUnpack(b);
    doParsimUnpacking(b,this->startHandover);
    doParsimUnpacking(b,this->ueId);
}

bool X2HandoverCommandIE::isStartHandover() const
{
    return this->startHandover;
}

void X2HandoverCommandIE::setStartHandover(bool startHandover)
{
    this->startHandover = startHandover;
}

MacNodeId X2HandoverCommandIE::getUeId() const
{
    return this->ueId;
}

void X2HandoverCommandIE::setUeId(MacNodeId ueId)
{
    this->ueId = ueId;
}

class X2HandoverCommandIEDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_startHandover,
        FIELD_ueId,
    };
  public:
    X2HandoverCommandIEDescriptor();
    virtual ~X2HandoverCommandIEDescriptor();

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

Register_ClassDescriptor(X2HandoverCommandIEDescriptor)

X2HandoverCommandIEDescriptor::X2HandoverCommandIEDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::X2HandoverCommandIE)), "simu5g::X2InformationElement")
{
    propertyNames = nullptr;
}

X2HandoverCommandIEDescriptor::~X2HandoverCommandIEDescriptor()
{
    delete[] propertyNames;
}

bool X2HandoverCommandIEDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<X2HandoverCommandIE *>(obj)!=nullptr;
}

const char **X2HandoverCommandIEDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *X2HandoverCommandIEDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int X2HandoverCommandIEDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int X2HandoverCommandIEDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_startHandover
        FD_ISEDITABLE,    // FIELD_ueId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *X2HandoverCommandIEDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "startHandover",
        "ueId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int X2HandoverCommandIEDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "startHandover") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ueId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *X2HandoverCommandIEDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_startHandover
        "simu5g::MacNodeId",    // FIELD_ueId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **X2HandoverCommandIEDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_startHandover: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *X2HandoverCommandIEDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_startHandover:
            if (!strcmp(propertyName, "getter")) return "isStartHandover";
            return nullptr;
        default: return nullptr;
    }
}

int X2HandoverCommandIEDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void X2HandoverCommandIEDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'X2HandoverCommandIE'", field);
    }
}

const char *X2HandoverCommandIEDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string X2HandoverCommandIEDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        case FIELD_startHandover: return bool2string(pp->isStartHandover());
        case FIELD_ueId: return int642string(num(pp->getUeId()));
        default: return "";
    }
}

void X2HandoverCommandIEDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        case FIELD_startHandover: pp->setStartHandover(string2bool(value)); break;
        case FIELD_ueId: pp->setUeId(MacNodeId(string2int64(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2HandoverCommandIE'", field);
    }
}

omnetpp::cValue X2HandoverCommandIEDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        case FIELD_startHandover: return pp->isStartHandover();
        case FIELD_ueId: return num(pp->getUeId());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'X2HandoverCommandIE' as cValue -- field index out of range?", field);
    }
}

void X2HandoverCommandIEDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        case FIELD_startHandover: pp->setStartHandover(value.boolValue()); break;
        case FIELD_ueId: pp->setUeId(MacNodeId(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2HandoverCommandIE'", field);
    }
}

const char *X2HandoverCommandIEDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr X2HandoverCommandIEDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void X2HandoverCommandIEDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    X2HandoverCommandIE *pp = omnetpp::fromAnyPtr<X2HandoverCommandIE>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2HandoverCommandIE'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

