# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####


bl_info = {
    "name": "OpenGL export / C",
    "author": "Krzysztof Solek",
    "blender": (2, 5, 7),
    "api": 35622,
    "location": "File > Import-Export",
    "description": "Export mesh data with UV's into C/OpenGL format",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

if "bpy" in locals():
    import imp
    if "export_ogl" in locals():
        imp.reload(export_ogl)


import os
import bpy
from bpy.props import CollectionProperty, StringProperty, BoolProperty
from bpy_extras.io_utils import ImportHelper, ExportHelper


class ExportOGL(bpy.types.Operator, ExportHelper):
    '''Export a whole scene or single object as an OpenGL / C include file with normals  and texture coordinates'''
    bl_idname = "export_ogl.ply"
    bl_label = "Export OpenGL"

    filename_ext = ".c"
    filter_glob = StringProperty(default="*.c", options={'HIDDEN'})

    entire_scene = BoolProperty(name="Entire Scene", description="Export all MESH object (Entire scene)", default=True)

    @classmethod
    def poll(cls, context):
        return context.active_object != None

    def execute(self, context):
        filepath = self.filepath
        filepath = bpy.path.ensure_ext(filepath, self.filename_ext)
        from . import export_ogl
        return export_ogl.export(filepath, self.entire_scene)

    def draw(self, context):
        layout = self.layout

        row = layout.row()
        row.prop(self, "entire_scene")

def menu_func_export(self, context):
    self.layout.operator(ExportOGL.bl_idname, text="OpenGL C function (.c)")


def register():
    bpy.utils.register_module(__name__)

    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_module(__name__)

    bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
