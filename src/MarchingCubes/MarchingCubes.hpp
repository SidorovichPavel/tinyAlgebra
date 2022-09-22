#pragma once

#include <vector>
#include <xutility>
#include <type_traits>

#include "..\glm\glm.hpp"
#include "..\Octree\Octree.hpp"

#define TA_MARCHING_CUBES_BEGIN namespace ta { namespace marching_cubes {
#define TA_MARCHING_CUBES_END };};

TA_MARCHING_CUBES_BEGIN

auto generate_cubes(::glm::vec3 _Pos, ::glm::vec3 _Size, float _Scale)
->std::pair<std::vector<::glm::vec3>, std::vector<uint32_t>>;

auto march_cubes(::glm::vec3 _Pos, ::glm::vec3 _Size, float _Step, float _IsoLvl, float(*_Fn)(::glm::vec3 v))
->std::tuple<std::vector<::glm::vec3>, std::vector<::glm::vec3>, std::vector<uint32_t>>;

auto march_cubes(GeneratingOctree& _SpaceTree)
->std::tuple<std::vector<::glm::vec3>, std::vector<::glm::vec3>, std::vector<uint32_t>>;

namespace numeric
{
	constexpr int8_t NumberOfCubeVertices = 8;
	constexpr int8_t NumberOfCubeEdges = 12;

	/*
	* VertexOffset lists the positions, relative to vertex0, of each of the 8 vertices of a cube
	* перечисляет позиции относительно вершины 0 каждой из 8 вершин куба
	*/
	extern const ::glm::vec3 VertexOffset[NumberOfCubeVertices];

	/*
	* EdgeConnection lists the index of the endpoint vertices for each of the 12 edges of the cube
	* перечисляет индекс вершин конечных точек для каждого из 12 ребер куба
	*/
	extern const std::pair<int32_t, int32_t> EdgeConnection[NumberOfCubeEdges];

	/*
	* EdgeDirection lists the direction vector (vertex1-vertex0) for each edge in the cube
	* выводит вектор направления(vertex1 - vertex0) для каждого ребра в кубе
	*/
	extern const ::glm::vec3 EdgeDirection[NumberOfCubeEdges];

	/*
	* For any edge, if one vertex is inside of the surface and the other is outside of the surface
	* then the edge intersects the surface
	* For each of the 8 vertices of the cube can be two possible states : either inside or outside of the surface
	* For any cube the are 2^8=256 possible sets of vertex states
	* This table lists the edges intersected by the surface for all 256 possible vertex states
	* There are 12 edges.  For each entry in the table, if edge #n is intersected, then bit #n is set to 1
	*/
	extern const int16_t CubeEdgeFlags[256];

	/*
	* For each of the possible vertex states listed in aiCubeEdgeFlags there is a specific
	* triangulation of the edge intersection points.
	* a2iTriangleConnectionTable lists all of them in the form of 0-5 edge triples with the list terminated by the invalid value -1.
	*
	* For example: a2iTriangleConnectionTable[3] list the 2 triangles formed when corner[0]
	* and corner[1] are inside of the surface, but the rest of the cube is not.
	* I found this table in an example program someone wrote long ago.
	*/
	extern const int8_t TriangleConnectionTable[256][16];

	/*
	* TetrahedronEdgeConnection lists the index of the endpoint vertices for each of the 6 edges of the tetrahedron
	* перечисляет индекс вершин конечной точки для каждого из 6 ребер тетраэдра
	*/
	extern const int32_t TetrahedronEdgeConnection[6][2];

	/*
	* TetrahedronEdgeConnection lists the index of vertices from a cube that made up each of the six tetrahedrons within the cube
	* перечисляет индексы вершин куба, из которых состоит каждый из шести тетраэдров внутри куба.
	*/
	extern const int32_t TetrahedronsInACube[6][4];

	/*
	* For any edge, if one vertex is inside of the surface and the other is outside of the surface
	* then the edge intersects the surface
	* For each of the 4 vertices of the tetrahedron can be two possible states : either inside or outside of the surface
	* For any tetrahedron the are 2^4=16 possible sets of vertex states
	* This table lists the edges intersected by the surface for all 16 possible vertex states
	* There are 6 edges.  For each entry in the table, if edge #n is intersected, then bit #n is set to 1
	*/
	extern const int32_t TetrahedronEdgeFlags[16];

	/*
	* For each of the possible vertex states listed in aiTetrahedronEdgeFlags there is a specific triangulation
	* of the edge intersection points.  a2iTetrahedronTriangles lists all of them in the form of
	* 0-2 edge triples with the list terminated by the invalid value -1.
	*/
	extern const int32_t TetrahedronTriangles[16][7];
}


TA_MARCHING_CUBES_END