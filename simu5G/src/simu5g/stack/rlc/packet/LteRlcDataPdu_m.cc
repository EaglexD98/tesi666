//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/rlc/packet/LteRlcDataPdu.msg.
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
#include "LteRlcDataPdu_m.h"

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

Register_Class(LteRlcDataPdu)

LteRlcDataPdu::LteRlcDataPdu() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::b(1));

}

LteRlcDataPdu::LteRlcDataPdu(const LteRlcDataPdu& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LteRlcDataPdu::~LteRlcDataPdu()
{
    for (size_t i = 0; i < sdu_arraysize; i++)
        dropAndDelete(this->sdu[i]);
    delete [] this->sdu;
    delete [] this->sduSize;
}

LteRlcDataPdu& LteRlcDataPdu::operator=(const LteRlcDataPdu& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LteRlcDataPdu::copy(const LteRlcDataPdu& other)
{
    this->rlcPduLength = other.rlcPduLength;
    for (size_t i = 0; i < sdu_arraysize; i++)
        dropAndDelete(this->sdu[i]);
    delete [] this->sdu;
    this->sdu = (other.sdu_arraysize==0) ? nullptr : new ::inet::Packet *[other.sdu_arraysize];
    sdu_arraysize = other.sdu_arraysize;
    for (size_t i = 0; i < sdu_arraysize; i++) {
        this->sdu[i] = other.sdu[i];
        if (this->sdu[i] != nullptr) {
            this->sdu[i] = this->sdu[i]->dup();
            take(this->sdu[i]);
            this->sdu[i]->setName(other.sdu[i]->getName());
        }
    }
    delete [] this->sduSize;
    this->sduSize = (other.sduSize_arraysize==0) ? nullptr : new ::size_t[other.sduSize_arraysize];
    sduSize_arraysize = other.sduSize_arraysize;
    for (size_t i = 0; i < sduSize_arraysize; i++) {
        this->sduSize[i] = other.sduSize[i];
    }
    this->pduSequenceNumber = other.pduSequenceNumber;
    this->framingInfo = other.framingInfo;
}

void LteRlcDataPdu::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->rlcPduLength);
    b->pack(sdu_arraysize);
    doParsimArrayPacking(b,this->sdu,sdu_arraysize);
    b->pack(sduSize_arraysize);
    doParsimArrayPacking(b,this->sduSize,sduSize_arraysize);
    doParsimPacking(b,this->pduSequenceNumber);
    doParsimPacking(b,this->framingInfo);
}

void LteRlcDataPdu::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->rlcPduLength);
    delete [] this->sdu;
    b->unpack(sdu_arraysize);
    if (sdu_arraysize == 0) {
        this->sdu = nullptr;
    } else {
        this->sdu = new ::inet::Packet *[sdu_arraysize];
        doParsimArrayUnpacking(b,this->sdu,sdu_arraysize);
    }
    delete [] this->sduSize;
    b->unpack(sduSize_arraysize);
    if (sduSize_arraysize == 0) {
        this->sduSize = nullptr;
    } else {
        this->sduSize = new ::size_t[sduSize_arraysize];
        doParsimArrayUnpacking(b,this->sduSize,sduSize_arraysize);
    }
    doParsimUnpacking(b,this->pduSequenceNumber);
    doParsimUnpacking(b,this->framingInfo);
}

int64_t LteRlcDataPdu::getRlcPduLength() const
{
    return this->rlcPduLength;
}

void LteRlcDataPdu::setRlcPduLength(int64_t rlcPduLength)
{
    handleChange();
    this->rlcPduLength = rlcPduLength;
}

size_t LteRlcDataPdu::getNumSdu() const
{
    return sdu_arraysize;
}

const ::inet::Packet * LteRlcDataPdu::getSdu(size_t k) const
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    return this->sdu[k];
}

void LteRlcDataPdu::setSduArraySize(size_t newSize)
{
    handleChange();
    ::inet::Packet * *sdu2 = (newSize==0) ? nullptr : new ::inet::Packet *[newSize];
    size_t minSize = sdu_arraysize < newSize ? sdu_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sdu2[i] = this->sdu[i];
    for (size_t i = minSize; i < newSize; i++)
        sdu2[i] = nullptr;
    for (size_t i = newSize; i < sdu_arraysize; i++)
        dropAndDelete(sdu[i]);
    delete [] this->sdu;
    this->sdu = sdu2;
    sdu_arraysize = newSize;
}

void LteRlcDataPdu::setSdu(size_t k, ::inet::Packet * sdu)
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    if (this->sdu[k] != nullptr) throw omnetpp::cRuntimeError("setSdu(): a value is already set, remove it first with removeSdu()");
    this->sdu[k] = sdu;
    if (this->sdu[k] != nullptr) take(this->sdu[k]);
}

::inet::Packet * LteRlcDataPdu::removeSdu(size_t k)
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    ::inet::Packet * retval = this->sdu[k];
    if (retval != nullptr) drop(retval);
    this->sdu[k] = nullptr;
    return retval;
}

void LteRlcDataPdu::insertSdu(size_t k, ::inet::Packet * sdu)
{
    if (k > sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sdu_arraysize + 1;
    ::inet::Packet * *sdu2 = new ::inet::Packet *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sdu2[i] = this->sdu[i];
    sdu2[k] = sdu;
    if (sdu2[k] != nullptr) take(sdu2[k]);
    for (i = k + 1; i < newSize; i++)
        sdu2[i] = this->sdu[i-1];
    delete [] this->sdu;
    this->sdu = sdu2;
    sdu_arraysize = newSize;
}

void LteRlcDataPdu::appendSdu(::inet::Packet * sdu)
{
    insertSdu(sdu_arraysize, sdu);
}

void LteRlcDataPdu::eraseSdu(size_t k)
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sdu_arraysize - 1;
    ::inet::Packet * *sdu2 = (newSize == 0) ? nullptr : new ::inet::Packet *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sdu2[i] = this->sdu[i];
    for (i = k; i < newSize; i++)
        sdu2[i] = this->sdu[i+1];
    if (this->sdu[k] != nullptr) dropAndDelete(this->sdu[k]);
    delete [] this->sdu;
    this->sdu = sdu2;
    sdu_arraysize = newSize;
}

size_t LteRlcDataPdu::getSduSizeArraySize() const
{
    return sduSize_arraysize;
}

::size_t LteRlcDataPdu::getSduSize(size_t k) const
{
    if (k >= sduSize_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sduSize_arraysize, (unsigned long)k);
    return this->sduSize[k];
}

void LteRlcDataPdu::setSduSizeArraySize(size_t newSize)
{
    handleChange();
    ::size_t *sduSize2 = (newSize==0) ? nullptr : new ::size_t[newSize];
    size_t minSize = sduSize_arraysize < newSize ? sduSize_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sduSize2[i] = this->sduSize[i];
    for (size_t i = minSize; i < newSize; i++)
        sduSize2[i] = 0;
    delete [] this->sduSize;
    this->sduSize = sduSize2;
    sduSize_arraysize = newSize;
}

void LteRlcDataPdu::setSduSize(size_t k, ::size_t sduSize)
{
    if (k >= sduSize_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sduSize_arraysize, (unsigned long)k);
    handleChange();
    this->sduSize[k] = sduSize;
}

void LteRlcDataPdu::insertSduSize(size_t k, ::size_t sduSize)
{
    if (k > sduSize_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sduSize_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sduSize_arraysize + 1;
    ::size_t *sduSize2 = new ::size_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sduSize2[i] = this->sduSize[i];
    sduSize2[k] = sduSize;
    for (i = k + 1; i < newSize; i++)
        sduSize2[i] = this->sduSize[i-1];
    delete [] this->sduSize;
    this->sduSize = sduSize2;
    sduSize_arraysize = newSize;
}

void LteRlcDataPdu::appendSduSize(::size_t sduSize)
{
    insertSduSize(sduSize_arraysize, sduSize);
}

void LteRlcDataPdu::eraseSduSize(size_t k)
{
    if (k >= sduSize_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sduSize_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sduSize_arraysize - 1;
    ::size_t *sduSize2 = (newSize == 0) ? nullptr : new ::size_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sduSize2[i] = this->sduSize[i];
    for (i = k; i < newSize; i++)
        sduSize2[i] = this->sduSize[i+1];
    delete [] this->sduSize;
    this->sduSize = sduSize2;
    sduSize_arraysize = newSize;
}

unsigned int LteRlcDataPdu::getPduSequenceNumber() const
{
    return this->pduSequenceNumber;
}

void LteRlcDataPdu::setPduSequenceNumber(unsigned int pduSequenceNumber)
{
    handleChange();
    this->pduSequenceNumber = pduSequenceNumber;
}

const FramingInfo& LteRlcDataPdu::getFramingInfo() const
{
    return this->framingInfo;
}

void LteRlcDataPdu::setFramingInfo(const FramingInfo& framingInfo)
{
    handleChange();
    this->framingInfo = framingInfo;
}

class LteRlcDataPduDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rlcPduLength,
        FIELD_sdu,
        FIELD_sduSize,
        FIELD_pduSequenceNumber,
        FIELD_framingInfo,
    };
  public:
    LteRlcDataPduDescriptor();
    virtual ~LteRlcDataPduDescriptor();

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

Register_ClassDescriptor(LteRlcDataPduDescriptor)

LteRlcDataPduDescriptor::LteRlcDataPduDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteRlcDataPdu)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LteRlcDataPduDescriptor::~LteRlcDataPduDescriptor()
{
    delete[] propertyNames;
}

bool LteRlcDataPduDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteRlcDataPdu *>(obj)!=nullptr;
}

const char **LteRlcDataPduDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteRlcDataPduDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteRlcDataPduDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LteRlcDataPduDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_rlcPduLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_sdu
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sduSize
        FD_ISEDITABLE,    // FIELD_pduSequenceNumber
        FD_ISCOMPOUND,    // FIELD_framingInfo
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LteRlcDataPduDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rlcPduLength",
        "sdu",
        "sduSize",
        "pduSequenceNumber",
        "framingInfo",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LteRlcDataPduDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rlcPduLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sdu") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sduSize") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pduSequenceNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "framingInfo") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LteRlcDataPduDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int64_t",    // FIELD_rlcPduLength
        "inet::Packet",    // FIELD_sdu
        "size_t",    // FIELD_sduSize
        "unsigned int",    // FIELD_pduSequenceNumber
        "simu5g::FramingInfo",    // FIELD_framingInfo
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LteRlcDataPduDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu: {
            static const char *names[] = { "sizeGetter", "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LteRlcDataPduDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu:
            if (!strcmp(propertyName, "sizeGetter")) return "getNumSdu";
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int LteRlcDataPduDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: return pp->getNumSdu();
        case FIELD_sduSize: return pp->getSduSizeArraySize();
        default: return 0;
    }
}

void LteRlcDataPduDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: pp->setSduArraySize(size); break;
        case FIELD_sduSize: pp->setSduSizeArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteRlcDataPdu'", field);
    }
}

const char *LteRlcDataPduDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: { const ::inet::Packet * value = pp->getSdu(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string LteRlcDataPduDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_rlcPduLength: return int642string(pp->getRlcPduLength());
        case FIELD_sdu: { auto obj = pp->getSdu(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_sduSize: return uint642string(pp->getSduSize(i));
        case FIELD_pduSequenceNumber: return ulong2string(pp->getPduSequenceNumber());
        case FIELD_framingInfo: return "";
        default: return "";
    }
}

void LteRlcDataPduDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_rlcPduLength: pp->setRlcPduLength(string2int64(value)); break;
        case FIELD_sduSize: pp->setSduSize(i,string2uint64(value)); break;
        case FIELD_pduSequenceNumber: pp->setPduSequenceNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcDataPdu'", field);
    }
}

omnetpp::cValue LteRlcDataPduDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_rlcPduLength: return pp->getRlcPduLength();
        case FIELD_sdu: return omnetpp::toAnyPtr(pp->getSdu(i)); break;
        case FIELD_sduSize: return (omnetpp::intval_t)(pp->getSduSize(i));
        case FIELD_pduSequenceNumber: return (omnetpp::intval_t)(pp->getPduSequenceNumber());
        case FIELD_framingInfo: return omnetpp::toAnyPtr(&pp->getFramingInfo()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteRlcDataPdu' as cValue -- field index out of range?", field);
    }
}

void LteRlcDataPduDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_rlcPduLength: pp->setRlcPduLength(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_sdu: pp->setSdu(i,omnetpp::fromAnyPtr<::inet::Packet>(value.pointerValue())); break;
        case FIELD_sduSize: pp->setSduSize(i,omnetpp::checked_int_cast<size_t>(value.intValue())); break;
        case FIELD_pduSequenceNumber: pp->setPduSequenceNumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcDataPdu'", field);
    }
}

const char *LteRlcDataPduDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu: return omnetpp::opp_typename(typeid(::inet::Packet));
        case FIELD_framingInfo: return omnetpp::opp_typename(typeid(FramingInfo));
        default: return nullptr;
    };
}

omnetpp::any_ptr LteRlcDataPduDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: return omnetpp::toAnyPtr(pp->getSdu(i)); break;
        case FIELD_framingInfo: return omnetpp::toAnyPtr(&pp->getFramingInfo()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteRlcDataPduDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcDataPdu *pp = omnetpp::fromAnyPtr<LteRlcDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: pp->setSdu(i,omnetpp::fromAnyPtr<::inet::Packet>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcDataPdu'", field);
    }
}

Register_Class(LteRlcUmDataPdu)

LteRlcUmDataPdu::LteRlcUmDataPdu() : ::simu5g::LteRlcDataPdu()
{
    this->setRlcPduLength(RLC_HEADER_UM);
    this->setChunkLength(inet::B(RLC_HEADER_UM));
}

LteRlcUmDataPdu::LteRlcUmDataPdu(const LteRlcUmDataPdu& other) : ::simu5g::LteRlcDataPdu(other)
{
    copy(other);
}

LteRlcUmDataPdu::~LteRlcUmDataPdu()
{
}

LteRlcUmDataPdu& LteRlcUmDataPdu::operator=(const LteRlcUmDataPdu& other)
{
    if (this == &other) return *this;
    ::simu5g::LteRlcDataPdu::operator=(other);
    copy(other);
    return *this;
}

void LteRlcUmDataPdu::copy(const LteRlcUmDataPdu& other)
{
}

void LteRlcUmDataPdu::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::LteRlcDataPdu::parsimPack(b);
}

void LteRlcUmDataPdu::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::LteRlcDataPdu::parsimUnpack(b);
}

class LteRlcUmDataPduDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    LteRlcUmDataPduDescriptor();
    virtual ~LteRlcUmDataPduDescriptor();

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

Register_ClassDescriptor(LteRlcUmDataPduDescriptor)

LteRlcUmDataPduDescriptor::LteRlcUmDataPduDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteRlcUmDataPdu)), "simu5g::LteRlcDataPdu")
{
    propertyNames = nullptr;
}

LteRlcUmDataPduDescriptor::~LteRlcUmDataPduDescriptor()
{
    delete[] propertyNames;
}

bool LteRlcUmDataPduDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteRlcUmDataPdu *>(obj)!=nullptr;
}

const char **LteRlcUmDataPduDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteRlcUmDataPduDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteRlcUmDataPduDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int LteRlcUmDataPduDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *LteRlcUmDataPduDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int LteRlcUmDataPduDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *LteRlcUmDataPduDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **LteRlcUmDataPduDescriptor::getFieldPropertyNames(int field) const
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

const char *LteRlcUmDataPduDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LteRlcUmDataPduDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LteRlcUmDataPduDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteRlcUmDataPdu'", field);
    }
}

const char *LteRlcUmDataPduDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LteRlcUmDataPduDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void LteRlcUmDataPduDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcUmDataPdu'", field);
    }
}

omnetpp::cValue LteRlcUmDataPduDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteRlcUmDataPdu' as cValue -- field index out of range?", field);
    }
}

void LteRlcUmDataPduDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcUmDataPdu'", field);
    }
}

const char *LteRlcUmDataPduDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr LteRlcUmDataPduDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteRlcUmDataPduDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcUmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcUmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcUmDataPdu'", field);
    }
}

Register_Class(LteRlcAmDataPdu)

LteRlcAmDataPdu::LteRlcAmDataPdu() : ::simu5g::LteRlcDataPdu()
{
    this->setRlcPduLength(RLC_HEADER_UM);
    this->setChunkLength(inet::B(RLC_HEADER_UM));

}

LteRlcAmDataPdu::LteRlcAmDataPdu(const LteRlcAmDataPdu& other) : ::simu5g::LteRlcDataPdu(other)
{
    copy(other);
}

LteRlcAmDataPdu::~LteRlcAmDataPdu()
{
}

LteRlcAmDataPdu& LteRlcAmDataPdu::operator=(const LteRlcAmDataPdu& other)
{
    if (this == &other) return *this;
    ::simu5g::LteRlcDataPdu::operator=(other);
    copy(other);
    return *this;
}

void LteRlcAmDataPdu::copy(const LteRlcAmDataPdu& other)
{
    this->pollStatus = other.pollStatus;
}

void LteRlcAmDataPdu::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::LteRlcDataPdu::parsimPack(b);
    doParsimPacking(b,this->pollStatus);
}

void LteRlcAmDataPdu::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::LteRlcDataPdu::parsimUnpack(b);
    doParsimUnpacking(b,this->pollStatus);
}

bool LteRlcAmDataPdu::getPollStatus() const
{
    return this->pollStatus;
}

void LteRlcAmDataPdu::setPollStatus(bool pollStatus)
{
    handleChange();
    this->pollStatus = pollStatus;
}

class LteRlcAmDataPduDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_pollStatus,
    };
  public:
    LteRlcAmDataPduDescriptor();
    virtual ~LteRlcAmDataPduDescriptor();

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

Register_ClassDescriptor(LteRlcAmDataPduDescriptor)

LteRlcAmDataPduDescriptor::LteRlcAmDataPduDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteRlcAmDataPdu)), "simu5g::LteRlcDataPdu")
{
    propertyNames = nullptr;
}

LteRlcAmDataPduDescriptor::~LteRlcAmDataPduDescriptor()
{
    delete[] propertyNames;
}

bool LteRlcAmDataPduDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteRlcAmDataPdu *>(obj)!=nullptr;
}

const char **LteRlcAmDataPduDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteRlcAmDataPduDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteRlcAmDataPduDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LteRlcAmDataPduDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_pollStatus
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LteRlcAmDataPduDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pollStatus",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LteRlcAmDataPduDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "pollStatus") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LteRlcAmDataPduDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_pollStatus
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LteRlcAmDataPduDescriptor::getFieldPropertyNames(int field) const
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

const char *LteRlcAmDataPduDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LteRlcAmDataPduDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LteRlcAmDataPduDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteRlcAmDataPdu'", field);
    }
}

const char *LteRlcAmDataPduDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LteRlcAmDataPduDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_pollStatus: return bool2string(pp->getPollStatus());
        default: return "";
    }
}

void LteRlcAmDataPduDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_pollStatus: pp->setPollStatus(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcAmDataPdu'", field);
    }
}

omnetpp::cValue LteRlcAmDataPduDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_pollStatus: return pp->getPollStatus();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteRlcAmDataPdu' as cValue -- field index out of range?", field);
    }
}

void LteRlcAmDataPduDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        case FIELD_pollStatus: pp->setPollStatus(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcAmDataPdu'", field);
    }
}

const char *LteRlcAmDataPduDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LteRlcAmDataPduDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteRlcAmDataPduDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteRlcAmDataPdu *pp = omnetpp::fromAnyPtr<LteRlcAmDataPdu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteRlcAmDataPdu'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

