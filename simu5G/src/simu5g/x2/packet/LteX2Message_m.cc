//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/x2/packet/LteX2Message.msg.
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
#include "LteX2Message_m.h"

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

Register_Enum(simu5g::LteX2MessageType, (simu5g::LteX2MessageType::X2_COMP_MSG, simu5g::LteX2MessageType::X2_HANDOVER_CONTROL_MSG, simu5g::LteX2MessageType::X2_HANDOVER_DATA_MSG, simu5g::LteX2MessageType::X2_DUALCONNECTIVITY_CONTROL_MSG, simu5g::LteX2MessageType::X2_DUALCONNECTIVITY_DATA_MSG, simu5g::LteX2MessageType::X2_UNKNOWN_MSG));

Register_Class(LteX2Message)

LteX2Message::LteX2Message() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::B(11));

}

LteX2Message::LteX2Message(const LteX2Message& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LteX2Message::~LteX2Message()
{
    for (size_t i = 0; i < ie_arraysize; i++)
        delete this->ie[i];
    delete [] this->ie;
}

LteX2Message& LteX2Message::operator=(const LteX2Message& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LteX2Message::copy(const LteX2Message& other)
{
    this->sourceId = other.sourceId;
    this->destinationId = other.destinationId;
    this->type = other.type;
    this->msgLength = other.msgLength;
    for (size_t i = 0; i < ie_arraysize; i++)
        delete this->ie[i];
    delete [] this->ie;
    this->ie = (other.ie_arraysize==0) ? nullptr : new X2InformationElement *[other.ie_arraysize];
    ie_arraysize = other.ie_arraysize;
    for (size_t i = 0; i < ie_arraysize; i++) {
        this->ie[i] = other.ie[i];
        if (this->ie[i] != nullptr) {
            this->ie[i] = this->ie[i]->dup();
        }
    }
}

void LteX2Message::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destinationId);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->msgLength);
    b->pack(ie_arraysize);
    doParsimArrayPacking(b,this->ie,ie_arraysize);
}

void LteX2Message::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destinationId);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->msgLength);
    delete [] this->ie;
    b->unpack(ie_arraysize);
    if (ie_arraysize == 0) {
        this->ie = nullptr;
    } else {
        this->ie = new X2InformationElement *[ie_arraysize];
        doParsimArrayUnpacking(b,this->ie,ie_arraysize);
    }
}

MacNodeId LteX2Message::getSourceId() const
{
    return this->sourceId;
}

void LteX2Message::setSourceId(MacNodeId sourceId)
{
    handleChange();
    this->sourceId = sourceId;
}

MacNodeId LteX2Message::getDestinationId() const
{
    return this->destinationId;
}

void LteX2Message::setDestinationId(MacNodeId destinationId)
{
    handleChange();
    this->destinationId = destinationId;
}

LteX2MessageType LteX2Message::getType() const
{
    return this->type;
}

void LteX2Message::setType(LteX2MessageType type)
{
    handleChange();
    this->type = type;
}

int64_t LteX2Message::getMsgLength() const
{
    return this->msgLength;
}

void LteX2Message::setMsgLength(int64_t msgLength)
{
    handleChange();
    this->msgLength = msgLength;
}

size_t LteX2Message::getIeArraySize() const
{
    return ie_arraysize;
}

const X2InformationElement * LteX2Message::getIe(size_t k) const
{
    if (k >= ie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ie_arraysize, (unsigned long)k);
    return this->ie[k];
}

void LteX2Message::setIeArraySize(size_t newSize)
{
    handleChange();
    X2InformationElement * *ie2 = (newSize==0) ? nullptr : new X2InformationElement *[newSize];
    size_t minSize = ie_arraysize < newSize ? ie_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        ie2[i] = this->ie[i];
    for (size_t i = minSize; i < newSize; i++)
        ie2[i] = nullptr;
    for (size_t i = newSize; i < ie_arraysize; i++)
        delete ie[i];
    delete [] this->ie;
    this->ie = ie2;
    ie_arraysize = newSize;
}

void LteX2Message::setIe(size_t k, X2InformationElement * ie)
{
    if (k >= ie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ie_arraysize, (unsigned long)k);
    handleChange();
    if (this->ie[k] != nullptr) throw omnetpp::cRuntimeError("setIe(): a value is already set, remove it first with removeIe()");
    this->ie[k] = ie;
    if (this->ie[k] != nullptr && this->ie[k]->isOwnedObject()) take((cOwnedObject*)this->ie[k]);
}

X2InformationElement * LteX2Message::removeIe(size_t k)
{
    if (k >= ie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ie_arraysize, (unsigned long)k);
    handleChange();
    X2InformationElement * retval = this->ie[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->ie[k] = nullptr;
    return retval;
}

void LteX2Message::insertIe(size_t k, X2InformationElement * ie)
{
    if (k > ie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ie_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ie_arraysize + 1;
    X2InformationElement * *ie2 = new X2InformationElement *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ie2[i] = this->ie[i];
    ie2[k] = ie;
    if (ie2[k] != nullptr && ie2[k]->isOwnedObject()) take((cOwnedObject*)ie2[k]);
    for (i = k + 1; i < newSize; i++)
        ie2[i] = this->ie[i-1];
    delete [] this->ie;
    this->ie = ie2;
    ie_arraysize = newSize;
}

void LteX2Message::appendIe(X2InformationElement * ie)
{
    insertIe(ie_arraysize, ie);
}

void LteX2Message::eraseIe(size_t k)
{
    if (k >= ie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ie_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ie_arraysize - 1;
    X2InformationElement * *ie2 = (newSize == 0) ? nullptr : new X2InformationElement *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ie2[i] = this->ie[i];
    for (i = k; i < newSize; i++)
        ie2[i] = this->ie[i+1];
    if (this->ie[k] != nullptr && this->ie[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->ie[k]); else delete this->ie[k];
    delete [] this->ie;
    this->ie = ie2;
    ie_arraysize = newSize;
}

class LteX2MessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destinationId,
        FIELD_type,
        FIELD_msgLength,
        FIELD_ie,
    };
  public:
    LteX2MessageDescriptor();
    virtual ~LteX2MessageDescriptor();

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

Register_ClassDescriptor(LteX2MessageDescriptor)

LteX2MessageDescriptor::LteX2MessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteX2Message)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LteX2MessageDescriptor::~LteX2MessageDescriptor()
{
    delete[] propertyNames;
}

bool LteX2MessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteX2Message *>(obj)!=nullptr;
}

const char **LteX2MessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteX2MessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteX2MessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LteX2MessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destinationId
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_msgLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_ie
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LteX2MessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destinationId",
        "type",
        "msgLength",
        "ie",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LteX2MessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destinationId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "msgLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "ie") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LteX2MessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simu5g::MacNodeId",    // FIELD_sourceId
        "simu5g::MacNodeId",    // FIELD_destinationId
        "simu5g::LteX2MessageType",    // FIELD_type
        "int64_t",    // FIELD_msgLength
        "simu5g::X2InformationElement",    // FIELD_ie
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LteX2MessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_ie: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LteX2MessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "simu5g::LteX2MessageType";
            return nullptr;
        case FIELD_ie:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int LteX2MessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_ie: return pp->getIeArraySize();
        default: return 0;
    }
}

void LteX2MessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_ie: pp->setIeArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteX2Message'", field);
    }
}

const char *LteX2MessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_ie: { const X2InformationElement * value = pp->getIe(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string LteX2MessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return int642string(num(pp->getSourceId()));
        case FIELD_destinationId: return int642string(num(pp->getDestinationId()));
        case FIELD_type: return enum2string(pp->getType(), "simu5g::LteX2MessageType");
        case FIELD_msgLength: return int642string(pp->getMsgLength());
        case FIELD_ie: { auto obj = pp->getIe(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void LteX2MessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(MacNodeId(string2int64(value))); break;
        case FIELD_destinationId: pp->setDestinationId(MacNodeId(string2int64(value))); break;
        case FIELD_msgLength: pp->setMsgLength(string2int64(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteX2Message'", field);
    }
}

omnetpp::cValue LteX2MessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return num(pp->getSourceId());
        case FIELD_destinationId: return num(pp->getDestinationId());
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_msgLength: return pp->getMsgLength();
        case FIELD_ie: return omnetpp::toAnyPtr(pp->getIe(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteX2Message' as cValue -- field index out of range?", field);
    }
}

void LteX2MessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(MacNodeId(value.intValue())); break;
        case FIELD_destinationId: pp->setDestinationId(MacNodeId(value.intValue())); break;
        case FIELD_msgLength: pp->setMsgLength(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_ie: pp->setIe(i,omnetpp::fromAnyPtr<X2InformationElement>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteX2Message'", field);
    }
}

const char *LteX2MessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ie: return omnetpp::opp_typename(typeid(X2InformationElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr LteX2MessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_ie: return omnetpp::toAnyPtr(pp->getIe(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteX2MessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteX2Message *pp = omnetpp::fromAnyPtr<LteX2Message>(object); (void)pp;
    switch (field) {
        case FIELD_ie: pp->setIe(i,omnetpp::fromAnyPtr<X2InformationElement>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteX2Message'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

