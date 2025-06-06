# automatically generated by the FlatBuffers compiler, do not modify

# namespace: minia

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class FlatMaterial(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = FlatMaterial()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsFlatMaterial(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # FlatMaterial
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # FlatMaterial
    def Id(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

    # FlatMaterial
    def Features(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from minia.FlatFeatures import FlatFeatures
            obj = FlatFeatures()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

def FlatMaterialStart(builder):
    builder.StartObject(2)

def Start(builder):
    FlatMaterialStart(builder)

def FlatMaterialAddId(builder, id):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(id), 0)

def AddId(builder, id):
    FlatMaterialAddId(builder, id)

def FlatMaterialAddFeatures(builder, features):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(features), 0)

def AddFeatures(builder, features):
    FlatMaterialAddFeatures(builder, features)

def FlatMaterialEnd(builder):
    return builder.EndObject()

def End(builder):
    return FlatMaterialEnd(builder)
