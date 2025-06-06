# automatically generated by the FlatBuffers compiler, do not modify

# namespace: minia

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class FlatStringArray(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = FlatStringArray()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsFlatStringArray(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # FlatStringArray
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # FlatStringArray
    def Value(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.String(a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 4))
        return ""

    # FlatStringArray
    def ValueLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FlatStringArray
    def ValueIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

def FlatStringArrayStart(builder):
    builder.StartObject(1)

def Start(builder):
    FlatStringArrayStart(builder)

def FlatStringArrayAddValue(builder, value):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(value), 0)

def AddValue(builder, value):
    FlatStringArrayAddValue(builder, value)

def FlatStringArrayStartValueVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def StartValueVector(builder, numElems):
    return FlatStringArrayStartValueVector(builder, numElems)

def FlatStringArrayEnd(builder):
    return builder.EndObject()

def End(builder):
    return FlatStringArrayEnd(builder)
