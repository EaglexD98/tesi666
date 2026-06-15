//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/compManager/compManagerProportional/X2CompProportionalReplyIE.msg.
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
#include "X2CompProportionalReplyIE_m.h"

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

Register_Enum(simu5g::CompRbStatus, (simu5g::CompRbStatus::AVAILABLE_RB, simu5g::CompRbStatus::NOT_AVAILABLE_RB));

Register_Class(X2CompProportionalReplyIE)

X2CompProportionalReplyIE::X2CompProportionalReplyIE() : ::simu5g::X2CompReplyIE()
{
    this->setLength(sizeof(uint32_t));
    this->setType(COMP_PROP_REPLY_IE);

}

X2CompProportionalReplyIE::X2CompProportionalReplyIE(const X2CompProportionalReplyIE& other) : ::simu5g::X2CompReplyIE(other)
{
    copy(other);
}

X2CompProportionalReplyIE::~X2CompProportionalReplyIE()
{
    delete [] this->allowedBlocksMap;
}

X2CompProportionalReplyIE& X2CompProportionalReplyIE::operator=(const X2CompProportionalReplyIE& other)
{
    if (this == &other) return *this;
    ::simu5g::X2CompReplyIE::operator=(other);
    copy(other);
    return *this;
}

void X2CompProportionalReplyIE::copy(const X2CompProportionalReplyIE& other)
{
    delete [] this->allowedBlocksMap;
    this->allowedBlocksMap = (other.allowedBlocksMap_arraysize==0) ? nullptr : new CompRbStatus[other.allowedBlocksMap_arraysize];
    allowedBlocksMap_arraysize = other.allowedBlocksMap_arraysize;
    for (size_t i = 0; i < allowedBlocksMap_arraysize; i++) {
        this->allowedBlocksMap[i] = other.allowedBlocksMap[i];
    }
}

void X2CompProportionalReplyIE::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::X2CompReplyIE::parsimPack(b);
    b->pack(allowedBlocksMap_arraysize);
    doParsimArrayPacking(b,this->allowedBlocksMap,allowedBlocksMap_arraysize);
}

void X2CompProportionalReplyIE::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::X2CompReplyIE::parsimUnpack(b);
    delete [] this->allowedBlocksMap;
    b->unpack(allowedBlocksMap_arraysize);
    if (allowedBlocksMap_arraysize == 0) {
        this->allowedBlocksMap = nullptr;
    } else {
        this->allowedBlocksMap = new CompRbStatus[allowedBlocksMap_arraysize];
        doParsimArrayUnpacking(b,this->allowedBlocksMap,allowedBlocksMap_arraysize);
    }
}

size_t X2CompProportionalReplyIE::getAllowedBlocksMapArraySize() const
{
    return allowedBlocksMap_arraysize;
}

CompRbStatus X2CompProportionalReplyIE::getAllowedBlocksMap(size_t k) const
{
    if (k >= allowedBlocksMap_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)allowedBlocksMap_arraysize, (unsigned long)k);
    return this->allowedBlocksMap[k];
}

void X2CompProportionalReplyIE::setAllowedBlocksMapArraySize(size_t newSize)
{
    CompRbStatus *allowedBlocksMap2 = (newSize==0) ? nullptr : new CompRbStatus[newSize];
    size_t minSize = allowedBlocksMap_arraysize < newSize ? allowedBlocksMap_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        allowedBlocksMap2[i] = this->allowedBlocksMap[i];
    for (size_t i = minSize; i < newSize; i++)
        allowedBlocksMap2[i] = static_cast<simu5g::CompRbStatus>(-1);
    delete [] this->allowedBlocksMap;
    this->allowedBlocksMap = allowedBlocksMap2;
    allowedBlocksMap_arraysize = newSize;
}

void X2CompProportionalReplyIE::setAllowedBlocksMap(size_t k, CompRbStatus allowedBlocksMap)
{
    if (k >= allowedBlocksMap_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)allowedBlocksMap_arraysize, (unsigned long)k);
    this->allowedBlocksMap[k] = allowedBlocksMap;
}

void X2CompProportionalReplyIE::insertAllowedBlocksMap(size_t k, CompRbStatus allowedBlocksMap)
{
    if (k > allowedBlocksMap_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)allowedBlocksMap_arraysize, (unsigned long)k);
    size_t newSize = allowedBlocksMap_arraysize + 1;
    CompRbStatus *allowedBlocksMap2 = new CompRbStatus[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        allowedBlocksMap2[i] = this->allowedBlocksMap[i];
    allowedBlocksMap2[k] = allowedBlocksMap;
    for (i = k + 1; i < newSize; i++)
        allowedBlocksMap2[i] = this->allowedBlocksMap[i-1];
    delete [] this->allowedBlocksMap;
    this->allowedBlocksMap = allowedBlocksMap2;
    allowedBlocksMap_arraysize = newSize;
}

void X2CompProportionalReplyIE::appendAllowedBlocksMap(CompRbStatus allowedBlocksMap)
{
    insertAllowedBlocksMap(allowedBlocksMap_arraysize, allowedBlocksMap);
}

void X2CompProportionalReplyIE::eraseAllowedBlocksMap(size_t k)
{
    if (k >= allowedBlocksMap_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)allowedBlocksMap_arraysize, (unsigned long)k);
    size_t newSize = allowedBlocksMap_arraysize - 1;
    CompRbStatus *allowedBlocksMap2 = (newSize == 0) ? nullptr : new CompRbStatus[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        allowedBlocksMap2[i] = this->allowedBlocksMap[i];
    for (i = k; i < newSize; i++)
        allowedBlocksMap2[i] = this->allowedBlocksMap[i+1];
    delete [] this->allowedBlocksMap;
    this->allowedBlocksMap = allowedBlocksMap2;
    allowedBlocksMap_arraysize = newSize;
}

class X2CompProportionalReplyIEDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_allowedBlocksMap,
    };
  public:
    X2CompProportionalReplyIEDescriptor();
    virtual ~X2CompProportionalReplyIEDescriptor();

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

Register_ClassDescriptor(X2CompProportionalReplyIEDescriptor)

X2CompProportionalReplyIEDescriptor::X2CompProportionalReplyIEDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::X2CompProportionalReplyIE)), "simu5g::X2CompReplyIE")
{
    propertyNames = nullptr;
}

X2CompProportionalReplyIEDescriptor::~X2CompProportionalReplyIEDescriptor()
{
    delete[] propertyNames;
}

bool X2CompProportionalReplyIEDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<X2CompProportionalReplyIE *>(obj)!=nullptr;
}

const char **X2CompProportionalReplyIEDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *X2CompProportionalReplyIEDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int X2CompProportionalReplyIEDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int X2CompProportionalReplyIEDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_allowedBlocksMap
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *X2CompProportionalReplyIEDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "allowedBlocksMap",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int X2CompProportionalReplyIEDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "allowedBlocksMap") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *X2CompProportionalReplyIEDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simu5g::CompRbStatus",    // FIELD_allowedBlocksMap
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **X2CompProportionalReplyIEDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_allowedBlocksMap: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *X2CompProportionalReplyIEDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_allowedBlocksMap:
            if (!strcmp(propertyName, "enum")) return "simu5g::CompRbStatus";
            return nullptr;
        default: return nullptr;
    }
}

int X2CompProportionalReplyIEDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        case FIELD_allowedBlocksMap: return pp->getAllowedBlocksMapArraySize();
        default: return 0;
    }
}

void X2CompProportionalReplyIEDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        case FIELD_allowedBlocksMap: pp->setAllowedBlocksMapArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'X2CompProportionalReplyIE'", field);
    }
}

const char *X2CompProportionalReplyIEDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string X2CompProportionalReplyIEDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        case FIELD_allowedBlocksMap: return enum2string(pp->getAllowedBlocksMap(i), "simu5g::CompRbStatus");
        default: return "";
    }
}

void X2CompProportionalReplyIEDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2CompProportionalReplyIE'", field);
    }
}

omnetpp::cValue X2CompProportionalReplyIEDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        case FIELD_allowedBlocksMap: return static_cast<int>(pp->getAllowedBlocksMap(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'X2CompProportionalReplyIE' as cValue -- field index out of range?", field);
    }
}

void X2CompProportionalReplyIEDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2CompProportionalReplyIE'", field);
    }
}

const char *X2CompProportionalReplyIEDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr X2CompProportionalReplyIEDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void X2CompProportionalReplyIEDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    X2CompProportionalReplyIE *pp = omnetpp::fromAnyPtr<X2CompProportionalReplyIE>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'X2CompProportionalReplyIE'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

