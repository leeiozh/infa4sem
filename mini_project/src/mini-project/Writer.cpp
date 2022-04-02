//
// Created by leeiozh on 23.03.2022.
//

#include "Writer.hpp"

#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkNew.h>

template <int DIM>
void Writer<DIM>::snapshot(std::shared_ptr<Mesh<DIM>> mesh) const {

    vtkSmartPointer<vtkStructuredGrid> structuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    vtkSmartPointer<vtkPoints> dumpPoints = vtkSmartPointer<vtkPoints>::New();

    auto refrInd = vtkSmartPointer<vtkDoubleArray>::New();
    refrInd->SetName("refrInd");

    if (DIM == 2) {
        int number = mesh->get_size();
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {

                auto node = mesh->get_point(i, j, 0);
                dumpPoints->InsertNextPoint(node.x, node.y, 0);
                refrInd->InsertNextValue(node.n);
            }
        }
        structuredGrid->SetDimensions(number, number, 1);
    } else {
        int number = static_cast<int>(mesh->get_size());
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                for (int k = 0; k < number; ++k) {
                    auto node = mesh->get_point(i, j, 0);
                    dumpPoints->InsertNextPoint(node.x, node.y, node.z);
                    refrInd->InsertNextValue(node.n);
                }
            }
        }
        structuredGrid->SetDimensions(number, number, number);
    }

    structuredGrid->SetPoints(dumpPoints);
    structuredGrid->GetPointData()->AddArray(refrInd);
    std::string fileName = path_ + "_back.vts";
    vtkSmartPointer<vtkXMLStructuredGridWriter> writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
    writer->SetFileName(fileName.c_str());
    writer->SetInputData(structuredGrid);
    writer->Write();
}

template <int DIM>
void Writer<DIM>::snapshot(int counter, const Ray<DIM> &ray) const {

    std::vector<std::array<double, DIM>> trajectory = ray.get_tract();
    vtkNew<vtkPoints> tract_points;

    for (auto &point_: trajectory) {
        if (DIM == 3) {
            tract_points->InsertNextPoint(point_[0], point_[1], point_[2]);
        } else {
            tract_points->InsertNextPoint(point_[0], point_[1], 0.);
        }
    }

    vtkNew<vtkPolyLine> polyLine;
    for (unsigned int i = 0; i < trajectory.size(); i++) {
        polyLine->GetPointIds()->InsertNextId(i);
    }

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    unstructuredGrid->SetPoints(tract_points.Get());
    unstructuredGrid->InsertNextCell(polyLine->GetCellType(), polyLine->GetPointIds());

    std::string fileName2 = path_ + std::to_string(counter) + "_trace.vtu";
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer2 = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer2->SetFileName(fileName2.c_str());
    writer2->SetInputData(unstructuredGrid);
    writer2->Write();

}

template
class Writer<2>;

template
class Writer<3>;