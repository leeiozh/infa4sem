//
// Created by leeiozh on 08.02.2022.
//

#include <set>
#include <cmath>
#include <gmsh.h>

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("dragon");

    // Let's merge an STL mesh that we would like to remesh (from the parent
    // directory):
    try {
        gmsh::merge("/home/leeiozh/miptbot/proga/infa4sem/lab1/inp/tor.stl");
    } catch(...) {
        gmsh::logger::write("Could not load STL mesh: bye!");
        gmsh::finalize();
        return 0;
    }

    double angle = 40;

    bool forceParametrizablePatches = true;

    bool includeBoundary = false;

    // Force curves to be split on given angle:
    double curveAngle = 180;

    gmsh::model::mesh::classifySurfaces(angle * M_PI / 180., includeBoundary,
                                        forceParametrizablePatches,
                                        curveAngle * M_PI / 180.);

    gmsh::model::mesh::createGeometry();

    // Create a volume from all the surfaces
    std::vector<std::pair<int, int> > s;
    gmsh::model::getEntities(s, 2);
    std::vector<int> sl;
    for(auto surf : s) sl.push_back(surf.second);
    int l = gmsh::model::geo::addSurfaceLoop(sl);
    gmsh::model::geo::addVolume({l});

    gmsh::model::geo::synchronize();


    int f = gmsh::model::mesh::field::add("MathEval");
    gmsh::model::mesh::field::setString(f, "F", "4");
    gmsh::model::mesh::field::setAsBackgroundMesh(f);

    gmsh::model::mesh::generate(3);

    gmsh::write("/home/leeiozh/miptbot/proga/infa4sem/lab1/out/tor.msh");

    // Launch the GUI to see the results:
    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();
    return 0;
}
