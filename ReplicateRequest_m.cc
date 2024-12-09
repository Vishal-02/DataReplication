//
// Generated file, do not edit! Created by opp_msgtool 6.1 from ReplicateRequest.msg.
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
#include "ReplicateRequest_m.h"

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

Register_Class(ReplicateRequest)

ReplicateRequest::ReplicateRequest(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ReplicateRequest::ReplicateRequest(const ReplicateRequest& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ReplicateRequest::~ReplicateRequest()
{
}

ReplicateRequest& ReplicateRequest::operator=(const ReplicateRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ReplicateRequest::copy(const ReplicateRequest& other)
{
    this->edgeId = other.edgeId;
    this->userId = other.userId;
    this->dataId = other.dataId;
    this->type = other.type;
    this->size = other.size;
}

void ReplicateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->edgeId);
    doParsimPacking(b,this->userId);
    doParsimPacking(b,this->dataId);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->size);
}

void ReplicateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->edgeId);
    doParsimUnpacking(b,this->userId);
    doParsimUnpacking(b,this->dataId);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->size);
}

int ReplicateRequest::getEdgeId() const
{
    return this->edgeId;
}

void ReplicateRequest::setEdgeId(int edgeId)
{
    this->edgeId = edgeId;
}

const char * ReplicateRequest::getUserId() const
{
    return this->userId.c_str();
}

void ReplicateRequest::setUserId(const char * userId)
{
    this->userId = userId;
}

const char * ReplicateRequest::getDataId() const
{
    return this->dataId.c_str();
}

void ReplicateRequest::setDataId(const char * dataId)
{
    this->dataId = dataId;
}

const char * ReplicateRequest::getType() const
{
    return this->type.c_str();
}

void ReplicateRequest::setType(const char * type)
{
    this->type = type;
}

int ReplicateRequest::getSize() const
{
    return this->size;
}

void ReplicateRequest::setSize(int size)
{
    this->size = size;
}

class ReplicateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_edgeId,
        FIELD_userId,
        FIELD_dataId,
        FIELD_type,
        FIELD_size,
    };
  public:
    ReplicateRequestDescriptor();
    virtual ~ReplicateRequestDescriptor();

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

Register_ClassDescriptor(ReplicateRequestDescriptor)

ReplicateRequestDescriptor::ReplicateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ReplicateRequest)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ReplicateRequestDescriptor::~ReplicateRequestDescriptor()
{
    delete[] propertyNames;
}

bool ReplicateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ReplicateRequest *>(obj)!=nullptr;
}

const char **ReplicateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ReplicateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ReplicateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int ReplicateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_edgeId
        FD_ISEDITABLE,    // FIELD_userId
        FD_ISEDITABLE,    // FIELD_dataId
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_size
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *ReplicateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "edgeId",
        "userId",
        "dataId",
        "type",
        "size",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int ReplicateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "edgeId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "userId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dataId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "size") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *ReplicateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_edgeId
        "string",    // FIELD_userId
        "string",    // FIELD_dataId
        "string",    // FIELD_type
        "int",    // FIELD_size
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **ReplicateRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *ReplicateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ReplicateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ReplicateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ReplicateRequest'", field);
    }
}

const char *ReplicateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ReplicateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_edgeId: return long2string(pp->getEdgeId());
        case FIELD_userId: return oppstring2string(pp->getUserId());
        case FIELD_dataId: return oppstring2string(pp->getDataId());
        case FIELD_type: return oppstring2string(pp->getType());
        case FIELD_size: return long2string(pp->getSize());
        default: return "";
    }
}

void ReplicateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_edgeId: pp->setEdgeId(string2long(value)); break;
        case FIELD_userId: pp->setUserId((value)); break;
        case FIELD_dataId: pp->setDataId((value)); break;
        case FIELD_type: pp->setType((value)); break;
        case FIELD_size: pp->setSize(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReplicateRequest'", field);
    }
}

omnetpp::cValue ReplicateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_edgeId: return pp->getEdgeId();
        case FIELD_userId: return pp->getUserId();
        case FIELD_dataId: return pp->getDataId();
        case FIELD_type: return pp->getType();
        case FIELD_size: return pp->getSize();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ReplicateRequest' as cValue -- field index out of range?", field);
    }
}

void ReplicateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_edgeId: pp->setEdgeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_userId: pp->setUserId(value.stringValue()); break;
        case FIELD_dataId: pp->setDataId(value.stringValue()); break;
        case FIELD_type: pp->setType(value.stringValue()); break;
        case FIELD_size: pp->setSize(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReplicateRequest'", field);
    }
}

const char *ReplicateRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ReplicateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ReplicateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ReplicateRequest *pp = omnetpp::fromAnyPtr<ReplicateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReplicateRequest'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

