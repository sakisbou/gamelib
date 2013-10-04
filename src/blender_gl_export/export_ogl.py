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

#############################################################
#	(C) Krzysztof Solek, Mielec 2012
#############################################################

import bpy
###########################################################
#
#       Global variables
#
###########################################################
obj_names=[]        # names of meshes in "C-suitable" format
vtx = []            # list of dictionaries for each mesh
face_start = []     # list of face starts
face_length = []    # list of face lengths
num_of_faces = 0    # total number of faces
vl = []             # list of vertices for each mesh
nl = []             # list of normals for each mesh
uvl =   []          # list of UV coords for each mesh
obj_mtx=[]          # list of local transformations for each object
obj_cnt =   0       # object count
max_vcnt=   0       # qty of vertices for biggest mesh

###########################################################
#
#   Round values of the 3D vector
#
###########################################################

def r3d(v):
    return round(v[0],6), round(v[1],6), round(v[2],6)

###########################################################
#
#   Round values of the 2D vector
#
###########################################################

def r2d(v):
    return round(v[0],6), round(v[1],6)


###########################################################
#
#   Convert object name to be suitable for C definition
#
###########################################################

def clearName(name):
    tmp=name.upper()
    ret=""
    for i in tmp:
        if (i in " ./\-+#$%^!@"):
            ret=ret+"_"
        else:
            ret=ret+i
    return ret


###########################################################
#
#   Build data for each object (MESH)
#
###########################################################

def buildData (obj, msh, name):
    global obj_cnt
    global obj_names     # names of meshes in "C-suitable" format
    global vtx           # list of dictionaries for each mesh
    global face_start    # list of face starts
    global face_length   # list of face lengths
    global num_of_faces  # total number of faces
    global vl            # list of vertices for each mesh
    global nl            # list of normals for each mesh
    global uvl           # list of UV coords for each mesh
    global obj_mtx       # list of local transformations for each object

    lvdic = {}           # local dictionary
    lvl = []             # local vertex list
    lnl = []             # local normal list
    luvl = []            # local uv list
    lvcnt = 0            # local vertices count
    isSmooth = False
    hasUV = True         # true by default, it will be verified below
    
    print("Building for: %s\n"%obj.name)

    if (len(msh.tessface_uv_textures)>0):
        if (msh.tessface_uv_textures.active is None):
            hasUV=False
    else:
        hasUV = False
     
    if (hasUV):
        activeUV = msh.tessface_uv_textures.active.data
        
    obj_names.append(clearName(name))
    obj_cnt+=1
    
    for i,f in enumerate(msh.tessfaces):
        face_start.append(lvcnt)
        fvc=0
        num_of_faces+=1
        isSmooth = f.use_smooth
        for j,v in enumerate(f.vertices):  
            vec = msh.vertices[v].co
            vec = r3d(vec)
            
            if (isSmooth):  # use vertex normal
                nor = msh.vertices[v].normal
            else:           # use face normal
                nor = f.normal
            
            nor = r3d(nor)
            
            if (hasUV):
                co = activeUV[i].uv[j]
                co = r2d(co)
            else:
                co = (0.0, 0.0)
            
            key = vec, nor, co

            lvdic[key] = lvcnt
            lvl.append(vec)
            lnl.append(nor)
            luvl.append(co)
            fvc+=1
            lvcnt+=1
        face_length.append(fvc)
        
    
    #update global lists and dictionaries
    vtx.append(lvdic)        
    vl.append(lvl)
    nl.append(lnl)
    uvl.append(luvl)

    obj_mtx.append(obj.matrix_local)

###########################################################
#
#   Write all vertices to single table
#
###########################################################
 
def writeVertices(file):
    
    file.write ("/*\n")
    file.write ("    vertices\n")
    file.write ("*/\n\n")
    
    #write verictes table
    file.write ("GLfloat vertex[]=\n{\n")
    for i, d in enumerate(vl):
        for j in range(0,len(d)):
            file.write ("  %ff, %ff, %ff"%tuple(vl[i][j]))
            if(j!=len(d)-1):
                file.write(",\n")
            else:
                file.write("\n")
    file.write("};\n\n")


###########################################################
#
#   Write all texture coordinates to single table
#
###########################################################
 
def writeTextureCoords(file):
    
    file.write ("/*\n")
    file.write ("    texture coordinates\n")
    file.write ("*/\n\n")
    
    #write verictes table
    file.write ("GLfloat texcoord[]=\n{\n")
    for i, d in enumerate(vl):
        for j in range(0,len(d)):


#            u=uvl[i][j][0]
#            v=uvl[i][j][1]
#            file.write ("    %ff,"%u)
#            v=-v
#            file.write (" %ff"%v)

            file.write ("  %ff, %ff"%tuple(uvl[i][j]))
            if(j!=len(d)-1):
                file.write(",\n")
            else:
                file.write("\n")
    file.write("};\n\n")


###########################################################
#
#   Write all normals to single table
#
###########################################################
 
def writeNormals(file):
    
    file.write ("/*\n")
    file.write ("    normals\n")
    file.write ("*/\n\n")
    
    #write verictes table
    file.write ("GLfloat normal[]=\n{\n")
    for i, d in enumerate(vl):
        for j in range(0,len(d)):
            file.write ("  %ff, %ff, %ff"%tuple(nl[i][j]))
            if(j!=len(d)-1):
                file.write(",\n")
            else:
                file.write("\n")
    file.write("};\n\n")


###########################################################
#
#   Write faces indexes into single table
#
###########################################################
    
def writeFaces(file):     

    file.write ("/*\n")
    file.write ("    polygon starts\n")
    file.write ("*/\n\n")
    
    file.write("GLuint polystart[]=\n{\n")
    
    for i in range(len(face_start)):
        file.write("  ")
        file.write(str(face_start[i]))
        if(i < len(face_start)-1):
            file.write(",\n")
    file.write("\n};\n\n")

    file.write ("/*\n")
    file.write ("    polygon lengths\n")
    file.write ("*/\n\n")
    
    file.write("GLuint polylength[]=\n{\n")
    
    for i in range(len(face_length)):
        file.write("  ")
        file.write(str(face_length[i]))
        if(i < len(face_length)-1):
            file.write(",\n")
    file.write("\n};\n\n")

    file.write ("/*\n")
    file.write ("    total number of polygons\n")
    file.write ("*/\n\n")
    
    file.write("GLuint num_of_polygons = ")
    file.write(str(num_of_faces))
    file.write(";\n\n\n\n\n")


###########################################################
#
#       Save data to C file
#
###########################################################
    
def save(filename):

    file = open(filename, "w", newline="\n")

    file.write("/*\n")
    file.write("      model\n")
    file.write("*/\n\n\n\n\n")
    file.write("#include <GL/gl.h>\n")
    file.write("#include \"../textures.h\"\n\n")
    file.write("void draw_object(void)\n{\n")

    writeVertices(file)
    writeTextureCoords(file)
    writeNormals(file)
    writeFaces(file)

    file.write ("/*\n")
    file.write ("      draw oject\n")
    file.write ("*/\n\n")

    file.write("  glBindTexture(GL_TEXTURE_2D, texture);\n")
    file.write("  glVertexPointer(3, GL_FLOAT, 0, vertex);\n")
    file.write("  glTexCoordPointer(2, GL_FLOAT, 0, texcoord);\n")
    file.write("  glNormalPointer(GL_FLOAT, 0, normal);\n")
    file.write("  glMultiDrawArrays(GL_TRIANGLE_FAN, polystart, polylength, num_of_polygons);\n")

    file.write("}\n\n\n\n\n")
        
    file.close()


###########################################################
#
#       Export MESH object. By default export whole scene
#
###########################################################

def export(filename="untitled.h", entire_scene=True):
    global obj_cnt
    global obj_names     # names of meshes in "C-suitable" format
    global vtx           # list of dictionaries for each mesh
    global faces         # list of lists
    global vl            # list of vertices for each mesh
    global nl            # list of normals for each mesh
    global uvl          # list of UV coords for each mesh
    global obj_mtx      # list of local transformations for each object

    print("--------------------------------------------------\n")
    print("Starting script:\n")
    print(filename)

    # clear all gloabl variables
    obj_names=[]    # names of meshes in "C-suitable" format
    vtx = []      # list of dictionaries for each mesh
    faces = []    # list of lists
    vl = []       # list of vertices for each mesh
    nl = []       # list of normals for each mesh
    uvl =   []    # list of UV coords for each mesh
    obj_mtx=[]  # list of local transformations for each object
    obj_cnt =   0   # object count
    max_vcnt=   0   # qty of vertices for biggest mesh


    sc = bpy.context.scene  # export MESHes from active scene

    if (entire_scene):
        for o in sc.objects:
            if (o.type=="MESH"):    # export ONLY meshes
                msh = o.to_mesh(sc,True,"PREVIEW") # prepare MESH
                buildData(o, msh, o.name)
                bpy.data.meshes.remove(msh)
    else:
        o = sc.objects.active
        msh = o.to_mesh(sc,True,'PREVIEW')
        buildData(o, msh, o.name)
        bpy.data.meshes.remove(msh)

    save(filename)    
    print("Done\n")
    return {'FINISHED'}


