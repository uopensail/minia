# automatically generated by the FlatBuffers compiler, do not modify

# namespace: minia

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class FlatMaterialCollection(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = FlatMaterialCollection()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsFlatMaterialCollection(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # FlatMaterialCollection
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # FlatMaterialCollection
    def Version(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

    # FlatMaterialCollection
    def Meterials(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from minia.FlatMaterial import FlatMaterial
            obj = FlatMaterial()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # FlatMaterialCollection
    def MeterialsLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FlatMaterialCollection
    def MeterialsIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

def FlatMaterialCollectionStart(builder):
    builder.StartObject(2)

def Start(builder):
    FlatMaterialCollectionStart(builder)

def FlatMaterialCollectionAddVersion(builder, version):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(version), 0)

def AddVersion(builder, version):
    FlatMaterialCollectionAddVersion(builder, version)

def FlatMaterialCollectionAddMeterials(builder, meterials):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(meterials), 0)

def AddMeterials(builder, meterials):
    FlatMaterialCollectionAddMeterials(builder, meterials)

def FlatMaterialCollectionStartMeterialsVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def StartMeterialsVector(builder, numElems):
    return FlatMaterialCollectionStartMeterialsVector(builder, numElems)

def FlatMaterialCollectionEnd(builder):
    return builder.EndObject()

def End(builder):
    return FlatMaterialCollectionEnd(builder)
