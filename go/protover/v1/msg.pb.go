// Code generated by protoc-gen-go.
// source: msg.proto
// DO NOT EDIT!

/*
Package protobuf is a generated protocol buffer package.

It is generated from these files:
	msg.proto

It has these top-level messages:
	A2B
*/
package protobuf

import proto "github.com/golang/protobuf/proto"
import math "math"

// Reference imports to suppress errors if they are not otherwise used.
var _ = proto.Marshal
var _ = math.Inf

type A2B struct {
	Field1           *uint64 `protobuf:"varint,1,req,name=field1" json:"field1,omitempty"`
	Field2           *uint64 `protobuf:"varint,2,opt,name=field2" json:"field2,omitempty"`
	XXX_unrecognized []byte  `json:"-"`
}

func (m *A2B) Reset()         { *m = A2B{} }
func (m *A2B) String() string { return proto.CompactTextString(m) }
func (*A2B) ProtoMessage()    {}

func (m *A2B) GetField1() uint64 {
	if m != nil && m.Field1 != nil {
		return *m.Field1
	}
	return 0
}

func (m *A2B) GetField2() uint64 {
	if m != nil && m.Field2 != nil {
		return *m.Field2
	}
	return 0
}

func init() {
}
