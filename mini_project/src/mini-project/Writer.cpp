//
// Created by leeiozh on 23.03.2022.
//

#include "Writer.hpp"

#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPPolyDataWriter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>


template <int DIM>
void Writer<DIM>::snapshot(const Mesh<DIM> &mesh) const {

    std::vector<std::vector<std::vector<Node>>> points = mesh.get_points();

    // Сетка в терминах VTK
    vtkSmartPointer<vtkStructuredGrid> structuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    // Точки сетки в терминах VTK
    vtkSmartPointer<vtkPoints> dumpPoints = vtkSmartPointer<vtkPoints>::New();

    // Скалярное поле на точках сетки
    auto refrInd = vtkSmartPointer<vtkDoubleArray>::New();
    refrInd->SetName("refrInd");

    if (DIM == 2) {
        // Обходим все точки нашей расчётной сетки
        int number = static_cast<int>(points.size());
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                // Вставляем новую точку в сетку VTK-снапшота
                dumpPoints->InsertNextPoint(points[i][j][0].x, points[i][j][0].y, points[i][j][0].z);
                refrInd->InsertNextValue(points[i][j][0].n);
            }
        }
        // Задаём размеры VTK-сетки (в точках, по трём осям)
        structuredGrid->SetDimensions(number, number, 1);
    } else {
        int number = static_cast<int>(points.size());
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                for (int k = 0; k < number; ++k) {
                    // Вставляем новую точку в сетку VTK-снапшота
                    dumpPoints->InsertNextPoint(points[i][j][k].x, points[i][j][k].y, points[i][j][k].z);
                    refrInd->InsertNextValue(points[i][j][k].n);
                }
            }
        }
        // Задаём размеры VTK-сетки (в точках, по трём осям)
        structuredGrid->SetDimensions(number, number, number);
    }

    // Грузим точки в сетку
    structuredGrid->SetPoints(dumpPoints);
    // Присоединяем векторное и скалярное поля к точкам
    structuredGrid->GetPointData()->AddArray(refrInd);

    // Создаём снапшот в файле с заданным именем
    std::string fileName = path_ + ".vts";
    vtkSmartPointer<vtkXMLStructuredGridWriter> writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
    writer->SetFileName(fileName.c_str());
    writer->SetInputData(structuredGrid);
    writer->Write();
}

template <int DIM>
void Writer<DIM>::snapshot(int counter, const Mesh<DIM> &mesh, const Ray<DIM> &ray) const {

    std::vector<std::vector<std::vector<Node>>> points = mesh.get_points();
    // Сетка в терминах VTK
    vtkSmartPointer<vtkStructuredGrid> structuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    // Точки сетки в терминах VTK
    vtkSmartPointer<vtkPoints> dumpPoints = vtkSmartPointer<vtkPoints>::New();

    // Скалярное поле на точках сетки
    auto refrInd = vtkSmartPointer<vtkDoubleArray>::New();
    refrInd->SetName("refrInd");

    if (DIM == 2) {
        // Обходим все точки нашей расчётной сетки
        int number = static_cast<int>(points.size());
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                // Вставляем новую точку в сетку VTK-снапшота
                dumpPoints->InsertNextPoint(points[i][j][0].x, points[i][j][0].y, points[i][j][0].z);
                refrInd->InsertNextValue(points[i][j][0].n);
            }
        }
        // Задаём размеры VTK-сетки (в точках, по трём осям)
        structuredGrid->SetDimensions(number, number, 1);
    } else {
        int number = static_cast<int>(points.size());
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                for (int k = 0; k < number; ++k) {
                    // Вставляем новую точку в сетку VTK-снапшота
                    dumpPoints->InsertNextPoint(points[i][j][k].x, points[i][j][k].y, points[i][j][k].z);
                    refrInd->InsertNextValue(points[i][j][k].n);
                }
            }
        }
        // Задаём размеры VTK-сетки (в точках, по трём осям)
        structuredGrid->SetDimensions(number, number, number);
    }

    // Грузим точки в сетку
    structuredGrid->SetPoints(dumpPoints);
    // Присоединяем векторное и скалярное поля к точкам
    structuredGrid->GetPointData()->AddArray(refrInd);

    std::vector<std::array<double, DIM>> trajectory = ray.get_tract();

    vtkNew<vtkPoints> tract_points;

    for (auto &point: trajectory) {
        if (DIM == 3) {
            tract_points->InsertNextPoint(point[0], point[1], point[2]);
        } else {
            tract_points->InsertNextPoint(point[0], point[1], 0.);
        }
    }

    vtkNew<vtkPolyLine> polyLine;
    polyLine->GetPointIds()->SetNumberOfIds(trajectory.size());
    vtkNew<vtkCellArray> cells;
    for (int i = 0; i < trajectory.size(); i++) {

        polyLine->GetPointIds()->SetId(i, i);

    }


    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(tract_points.Get());
//    polyData->SetLines(cells.Get());

//    vtkSmartPointer<vtkPolyDataMapper> mapper;
//    mapper->SetInputData(polyData);
//
//    vtkSmartPointer<vtkNamedColors> colors;
//
//    vtkSmartPointer<vtkActor> actor;
//    actor->SetMapper(mapper);
//    actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

    // Создаём снапшот в файле с заданным именем
    std::string fileName = path_ + std::to_string(counter) + "back.vts";
    std::string fileName2 = path_ + std::to_string(counter) + "trace.vts";
    vtkSmartPointer<vtkXMLStructuredGridWriter> writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
    writer->SetFileName(fileName.c_str());
    writer->SetInputData(structuredGrid);
    writer->Write();

    vtkSmartPointer<vtkXMLPPolyDataWriter> writer2 = vtkSmartPointer<vtkXMLPPolyDataWriter>::New();
    writer2->SetFileName(fileName2.c_str());

    writer2->SetInputData(polyData.Get());
    writer2->Write();
}

template
class Writer<2>;

template
class Writer<3>;
