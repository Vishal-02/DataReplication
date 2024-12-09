//
// Generated file, do not edit! Created by opp_msgtool 6.1 from ReplicateRequest.msg.
//

#ifndef __REPLICATEREQUEST_M_H
#define __REPLICATEREQUEST_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class ReplicateRequest;
/**
 * Class generated from <tt>ReplicateRequest.msg:1</tt> by opp_msgtool.
 * <pre>
 * message ReplicateRequest
 * {
 *     int edgeId; // ID of the edge the original request was made to
 *     string userId; // ID of the user that made the request
 *     string dataId; // ID of the requested data
 *     string type;
 *     int size;
 * }
 * </pre>
 */
class ReplicateRequest : public ::omnetpp::cMessage
{
  protected:
    int edgeId = 0;
    omnetpp::opp_string userId;
    omnetpp::opp_string dataId;
    omnetpp::opp_string type;
    int size = 0;

  private:
    void copy(const ReplicateRequest& other);

  protected:
    bool operator==(const ReplicateRequest&) = delete;

  public:
    ReplicateRequest(const char *name=nullptr, short kind=0);
    ReplicateRequest(const ReplicateRequest& other);
    virtual ~ReplicateRequest();
    ReplicateRequest& operator=(const ReplicateRequest& other);
    virtual ReplicateRequest *dup() const override {return new ReplicateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getEdgeId() const;
    virtual void setEdgeId(int edgeId);

    virtual const char * getUserId() const;
    virtual void setUserId(const char * userId);

    virtual const char * getDataId() const;
    virtual void setDataId(const char * dataId);

    virtual const char * getType() const;
    virtual void setType(const char * type);

    virtual int getSize() const;
    virtual void setSize(int size);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ReplicateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ReplicateRequest& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline ReplicateRequest *fromAnyPtr(any_ptr ptr) { return check_and_cast<ReplicateRequest*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __REPLICATEREQUEST_M_H

