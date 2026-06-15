//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/mac/packet/LteMacPdu.msg.
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
#include "LteMacPdu_m.h"

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

Register_Class(LteMacPdu)

LteMacPdu::LteMacPdu() : ::inet::FieldsChunk()
{
}

LteMacPdu::LteMacPdu(const LteMacPdu& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LteMacPdu::~LteMacPdu()
{
    for (size_t i = 0; i < sdu_arraysize; i++)
        dropAndDelete(this->sdu[i]);
    delete [] this->sdu;
    for (size_t i = 0; i < ce_arraysize; i++)
        delete this->ce[i];
    delete [] this->ce;
}

LteMacPdu& LteMacPdu::operator=(const LteMacPdu& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LteMacPdu::copy(const LteMacPdu& other)
{
    this->macPduId_ = other.macPduId_;
    this->macPduLength_ = other.macPduLength_;
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
    for (size_t i = 0; i < ce_arraysize; i++)
        delete this->ce[i];
    delete [] this->ce;
    this->ce = (other.ce_arraysize==0) ? nullptr : new MacControlElement *[other.ce_arraysize];
    ce_arraysize = other.ce_arraysize;
    for (size_t i = 0; i < ce_arraysize; i++) {
        this->ce[i] = other.ce[i];
        if (this->ce[i] != nullptr) {
            this->ce[i] = this->ce[i]->dup();
        }
    }
    this->headerLength = other.headerLength;
    this->macPduId = other.macPduId;
// cplusplus {{
    macPduLength_ = other.macPduLength_;
    macPduId_ = other.macPduId_;

    // duplication of the SDU queue duplicates all packets but not
    // the ControlInfo - iterate over all packets and restore ControlInfo if necessary
    for (size_t idx = 0; idx < sdu_arraysize; idx++) {
        Packet *p1 = sdu[idx];
        Packet *p2 = other.sdu[idx];
        if (p1->getControlInfo() == nullptr && p2->getControlInfo() != nullptr) {
            p1->setControlInfo(p2->getControlInfo()->dup());
        }
    }
// }}
}

void LteMacPdu::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->macPduId_);
    doParsimPacking(b,this->macPduLength_);
    b->pack(sdu_arraysize);
    doParsimArrayPacking(b,this->sdu,sdu_arraysize);
    b->pack(ce_arraysize);
    doParsimArrayPacking(b,this->ce,ce_arraysize);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->macPduId);
}

void LteMacPdu::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->macPduId_);
    doParsimUnpacking(b,this->macPduLength_);
    delete [] this->sdu;
    b->unpack(sdu_arraysize);
    if (sdu_arraysize == 0) {
        this->sdu = nullptr;
    } else {
        this->sdu = new ::inet::Packet *[sdu_arraysize];
        doParsimArrayUnpacking(b,this->sdu,sdu_arraysize);
    }
    delete [] this->ce;
    b->unpack(ce_arraysize);
    if (ce_arraysize == 0) {
        this->ce = nullptr;
    } else {
        this->ce = new MacControlElement *[ce_arraysize];
        doParsimArrayUnpacking(b,this->ce,ce_arraysize);
    }
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->macPduId);
}

int64_t LteMacPdu::getMacPduId_() const
{
    return this->macPduId_;
}

void LteMacPdu::setMacPduId_(int64_t macPduId_)
{
    handleChange();
    this->macPduId_ = macPduId_;
}

int64_t LteMacPdu::getMacPduLength_() const
{
    return this->macPduLength_;
}

void LteMacPdu::setMacPduLength_(int64_t macPduLength_)
{
    handleChange();
    this->macPduLength_ = macPduLength_;
}

size_t LteMacPdu::getSduArraySize() const
{
    return sdu_arraysize;
}

const ::inet::Packet * LteMacPdu::getSduPtr(size_t k) const
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    return this->sdu[k];
}

void LteMacPdu::setSduArraySize(size_t newSize)
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

void LteMacPdu::setSdu(size_t k, ::inet::Packet * sdu)
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    if (this->sdu[k] != nullptr) throw omnetpp::cRuntimeError("setSdu(): a value is already set, remove it first with removeSdu()");
    this->sdu[k] = sdu;
    if (this->sdu[k] != nullptr) take(this->sdu[k]);
}

::inet::Packet * LteMacPdu::removeSdu(size_t k)
{
    if (k >= sdu_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sdu_arraysize, (unsigned long)k);
    handleChange();
    ::inet::Packet * retval = this->sdu[k];
    if (retval != nullptr) drop(retval);
    this->sdu[k] = nullptr;
    return retval;
}

void LteMacPdu::insertSdu(size_t k, ::inet::Packet * sdu)
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

void LteMacPdu::appendSdu(::inet::Packet * sdu)
{
    insertSdu(sdu_arraysize, sdu);
}

void LteMacPdu::eraseSdu(size_t k)
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

size_t LteMacPdu::getCeArraySize() const
{
    return ce_arraysize;
}

const MacControlElement * LteMacPdu::getCe(size_t k) const
{
    if (k >= ce_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ce_arraysize, (unsigned long)k);
    return this->ce[k];
}

void LteMacPdu::setCeArraySize(size_t newSize)
{
    handleChange();
    MacControlElement * *ce2 = (newSize==0) ? nullptr : new MacControlElement *[newSize];
    size_t minSize = ce_arraysize < newSize ? ce_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        ce2[i] = this->ce[i];
    for (size_t i = minSize; i < newSize; i++)
        ce2[i] = nullptr;
    for (size_t i = newSize; i < ce_arraysize; i++)
        delete ce[i];
    delete [] this->ce;
    this->ce = ce2;
    ce_arraysize = newSize;
}

void LteMacPdu::setCe(size_t k, MacControlElement * ce)
{
    if (k >= ce_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ce_arraysize, (unsigned long)k);
    handleChange();
    if (this->ce[k] != nullptr) throw omnetpp::cRuntimeError("setCe(): a value is already set, remove it first with removeCe()");
    this->ce[k] = ce;
    if (this->ce[k] != nullptr && this->ce[k]->isOwnedObject()) take((cOwnedObject*)this->ce[k]);
}

MacControlElement * LteMacPdu::removeCe(size_t k)
{
    if (k >= ce_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ce_arraysize, (unsigned long)k);
    handleChange();
    MacControlElement * retval = this->ce[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->ce[k] = nullptr;
    return retval;
}

void LteMacPdu::insertCe(size_t k, MacControlElement * ce)
{
    if (k > ce_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ce_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ce_arraysize + 1;
    MacControlElement * *ce2 = new MacControlElement *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ce2[i] = this->ce[i];
    ce2[k] = ce;
    if (ce2[k] != nullptr && ce2[k]->isOwnedObject()) take((cOwnedObject*)ce2[k]);
    for (i = k + 1; i < newSize; i++)
        ce2[i] = this->ce[i-1];
    delete [] this->ce;
    this->ce = ce2;
    ce_arraysize = newSize;
}

void LteMacPdu::appendCe(MacControlElement * ce)
{
    insertCe(ce_arraysize, ce);
}

void LteMacPdu::eraseCe(size_t k)
{
    if (k >= ce_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ce_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ce_arraysize - 1;
    MacControlElement * *ce2 = (newSize == 0) ? nullptr : new MacControlElement *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ce2[i] = this->ce[i];
    for (i = k; i < newSize; i++)
        ce2[i] = this->ce[i+1];
    if (this->ce[k] != nullptr && this->ce[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->ce[k]); else delete this->ce[k];
    delete [] this->ce;
    this->ce = ce2;
    ce_arraysize = newSize;
}

unsigned int LteMacPdu::getHeaderLength() const
{
    return this->headerLength;
}

void LteMacPdu::setHeaderLength(unsigned int headerLength)
{
    handleChange();
// cplusplus {{
    this->setChunkLength(B(macPduLength_ + headerLength)); // use the headerLength parameter
// }}
    this->headerLength = headerLength;
}

long LteMacPdu::getMacPduId() const
{
    return this->macPduId;
}

void LteMacPdu::setMacPduId(long macPduId)
{
    handleChange();
    this->macPduId = macPduId;
}

class LteMacPduDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_macPduId_,
        FIELD_macPduLength_,
        FIELD_sdu,
        FIELD_ce,
        FIELD_headerLength,
        FIELD_macPduId,
    };
  public:
    LteMacPduDescriptor();
    virtual ~LteMacPduDescriptor();

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

Register_ClassDescriptor(LteMacPduDescriptor)

LteMacPduDescriptor::LteMacPduDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::LteMacPdu)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LteMacPduDescriptor::~LteMacPduDescriptor()
{
    delete[] propertyNames;
}

bool LteMacPduDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LteMacPdu *>(obj)!=nullptr;
}

const char **LteMacPduDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LteMacPduDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LteMacPduDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int LteMacPduDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_macPduId_
        FD_ISEDITABLE,    // FIELD_macPduLength_
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_sdu
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_ce
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_macPduId
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *LteMacPduDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "macPduId_",
        "macPduLength_",
        "sdu",
        "ce",
        "headerLength",
        "macPduId",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int LteMacPduDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "macPduId_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "macPduLength_") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sdu") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ce") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "macPduId") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *LteMacPduDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int64_t",    // FIELD_macPduId_
        "int64_t",    // FIELD_macPduLength_
        "inet::Packet",    // FIELD_sdu
        "simu5g::MacControlElement",    // FIELD_ce
        "unsigned int",    // FIELD_headerLength
        "long",    // FIELD_macPduId
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **LteMacPduDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu: {
            static const char *names[] = { "owned", "getter",  nullptr };
            return names;
        }
        case FIELD_ce: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LteMacPduDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu:
            if (!strcmp(propertyName, "owned")) return "";
            if (!strcmp(propertyName, "getter")) return "getSduPtr";
            return nullptr;
        case FIELD_ce:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int LteMacPduDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: return pp->getSduArraySize();
        case FIELD_ce: return pp->getCeArraySize();
        default: return 0;
    }
}

void LteMacPduDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: pp->setSduArraySize(size); break;
        case FIELD_ce: pp->setCeArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LteMacPdu'", field);
    }
}

const char *LteMacPduDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: { const ::inet::Packet * value = pp->getSduPtr(i); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_ce: { const MacControlElement * value = pp->getCe(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string LteMacPduDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_macPduId_: return int642string(pp->getMacPduId_());
        case FIELD_macPduLength_: return int642string(pp->getMacPduLength_());
        case FIELD_sdu: { auto obj = pp->getSduPtr(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_ce: { auto obj = pp->getCe(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_headerLength: return ulong2string(pp->getHeaderLength());
        case FIELD_macPduId: return long2string(pp->getMacPduId());
        default: return "";
    }
}

void LteMacPduDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_macPduId_: pp->setMacPduId_(string2int64(value)); break;
        case FIELD_macPduLength_: pp->setMacPduLength_(string2int64(value)); break;
        case FIELD_headerLength: pp->setHeaderLength(string2ulong(value)); break;
        case FIELD_macPduId: pp->setMacPduId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteMacPdu'", field);
    }
}

omnetpp::cValue LteMacPduDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_macPduId_: return pp->getMacPduId_();
        case FIELD_macPduLength_: return pp->getMacPduLength_();
        case FIELD_sdu: return omnetpp::toAnyPtr(pp->getSduPtr(i)); break;
        case FIELD_ce: return omnetpp::toAnyPtr(pp->getCe(i)); break;
        case FIELD_headerLength: return (omnetpp::intval_t)(pp->getHeaderLength());
        case FIELD_macPduId: return (omnetpp::intval_t)(pp->getMacPduId());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LteMacPdu' as cValue -- field index out of range?", field);
    }
}

void LteMacPduDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_macPduId_: pp->setMacPduId_(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_macPduLength_: pp->setMacPduLength_(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_sdu: pp->setSdu(i,omnetpp::fromAnyPtr<::inet::Packet>(value.pointerValue())); break;
        case FIELD_ce: pp->setCe(i,omnetpp::fromAnyPtr<MacControlElement>(value.pointerValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_macPduId: pp->setMacPduId(omnetpp::checked_int_cast<long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteMacPdu'", field);
    }
}

const char *LteMacPduDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdu: return omnetpp::opp_typename(typeid(::inet::Packet));
        case FIELD_ce: return omnetpp::opp_typename(typeid(MacControlElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr LteMacPduDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: return omnetpp::toAnyPtr(pp->getSduPtr(i)); break;
        case FIELD_ce: return omnetpp::toAnyPtr(pp->getCe(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LteMacPduDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LteMacPdu *pp = omnetpp::fromAnyPtr<LteMacPdu>(object); (void)pp;
    switch (field) {
        case FIELD_sdu: pp->setSdu(i,omnetpp::fromAnyPtr<::inet::Packet>(ptr)); break;
        case FIELD_ce: pp->setCe(i,omnetpp::fromAnyPtr<MacControlElement>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LteMacPdu'", field);
    }
}

Register_Class(MacControlElement)

MacControlElement::MacControlElement() : ::omnetpp::cObject()
{
}

MacControlElement::MacControlElement(const MacControlElement& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

MacControlElement::~MacControlElement()
{
}

MacControlElement& MacControlElement::operator=(const MacControlElement& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void MacControlElement::copy(const MacControlElement& other)
{
    this->timestamp = other.timestamp;
}

void MacControlElement::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->timestamp);
}

void MacControlElement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->timestamp);
}

double MacControlElement::getTimestamp() const
{
    return this->timestamp;
}

void MacControlElement::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class MacControlElementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_timestamp,
    };
  public:
    MacControlElementDescriptor();
    virtual ~MacControlElementDescriptor();

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

Register_ClassDescriptor(MacControlElementDescriptor)

MacControlElementDescriptor::MacControlElementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::MacControlElement)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

MacControlElementDescriptor::~MacControlElementDescriptor()
{
    delete[] propertyNames;
}

bool MacControlElementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MacControlElement *>(obj)!=nullptr;
}

const char **MacControlElementDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MacControlElementDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MacControlElementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int MacControlElementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *MacControlElementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "timestamp",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int MacControlElementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *MacControlElementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **MacControlElementDescriptor::getFieldPropertyNames(int field) const
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

const char *MacControlElementDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int MacControlElementDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MacControlElementDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MacControlElement'", field);
    }
}

const char *MacControlElementDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MacControlElementDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void MacControlElementDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacControlElement'", field);
    }
}

omnetpp::cValue MacControlElementDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MacControlElement' as cValue -- field index out of range?", field);
    }
}

void MacControlElementDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacControlElement'", field);
    }
}

const char *MacControlElementDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr MacControlElementDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MacControlElementDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MacControlElement *pp = omnetpp::fromAnyPtr<MacControlElement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacControlElement'", field);
    }
}

Register_Class(MacBsr)

MacBsr::MacBsr() : ::simu5g::MacControlElement()
{
}

MacBsr::MacBsr(const MacBsr& other) : ::simu5g::MacControlElement(other)
{
    copy(other);
}

MacBsr::~MacBsr()
{
}

MacBsr& MacBsr::operator=(const MacBsr& other)
{
    if (this == &other) return *this;
    ::simu5g::MacControlElement::operator=(other);
    copy(other);
    return *this;
}

void MacBsr::copy(const MacBsr& other)
{
    this->size = other.size;
}

void MacBsr::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::simu5g::MacControlElement::parsimPack(b);
    doParsimPacking(b,this->size);
}

void MacBsr::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::simu5g::MacControlElement::parsimUnpack(b);
    doParsimUnpacking(b,this->size);
}

int MacBsr::getSize() const
{
    return this->size;
}

void MacBsr::setSize(int size)
{
    this->size = size;
}

class MacBsrDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_size,
    };
  public:
    MacBsrDescriptor();
    virtual ~MacBsrDescriptor();

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

Register_ClassDescriptor(MacBsrDescriptor)

MacBsrDescriptor::MacBsrDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::MacBsr)), "simu5g::MacControlElement")
{
    propertyNames = nullptr;
}

MacBsrDescriptor::~MacBsrDescriptor()
{
    delete[] propertyNames;
}

bool MacBsrDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MacBsr *>(obj)!=nullptr;
}

const char **MacBsrDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MacBsrDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MacBsrDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int MacBsrDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_size
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *MacBsrDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "size",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int MacBsrDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "size") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *MacBsrDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_size
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **MacBsrDescriptor::getFieldPropertyNames(int field) const
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

const char *MacBsrDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int MacBsrDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MacBsrDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MacBsr'", field);
    }
}

const char *MacBsrDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MacBsrDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        case FIELD_size: return long2string(pp->getSize());
        default: return "";
    }
}

void MacBsrDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        case FIELD_size: pp->setSize(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacBsr'", field);
    }
}

omnetpp::cValue MacBsrDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        case FIELD_size: return pp->getSize();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MacBsr' as cValue -- field index out of range?", field);
    }
}

void MacBsrDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        case FIELD_size: pp->setSize(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacBsr'", field);
    }
}

const char *MacBsrDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr MacBsrDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MacBsrDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MacBsr *pp = omnetpp::fromAnyPtr<MacBsr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MacBsr'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

