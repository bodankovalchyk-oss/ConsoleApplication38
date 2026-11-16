
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Point
{
    int x;
    int y;
};

class Shape
{
protected:
    string type;

public:
    Shape(string t) : type(t) {}

    virtual void Print() const = 0;
    virtual void Save(ofstream& file) const = 0;

    virtual ~Shape() {}
};

class Line : public Shape
{
private:
    Point start;
    Point end;

public:
    Line(Point s, Point e) : Shape("Line"), start(s), end(e) {}

    void Print() const override
    {
        cout << "Line" << endl;
        cout << "Start: (" << start.x << ", " << start.y << ")" << endl;
        cout << "End: (" << end.x << ", " << end.y << ")" << endl;
    }

    void Save(ofstream& file) const override
    {
        file << type << endl;
        file << start.x << " " << start.y << endl;
        file << end.x << " " << end.y << endl;
    }

    ~Line() override = default;
};

class Rectangle : public Shape
{
private:
    Point topLeft;
    int width;
    int height;

public:
    Rectangle(Point p, int w, int h)
        : Shape("Rectangle"), topLeft(p), width(w), height(h) {
    }

    void Print() const override
    {
        cout << "Rectangle" << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    cout << "* ";
                else
                    cout << "  ";
            }
            cout << endl;
        }
    }

    void Save(ofstream& file) const override
    {
        file << type << endl;
        file << topLeft.x << " " << topLeft.y << endl;
        file << width << " " << height << endl;
    }

    ~Rectangle() override = default;
};

class Polyline : public Shape
{
private:
    vector<Point> points;

public:
    Polyline(const vector<Point>& p)
        : Shape("Polyline"), points(p) {
    }

    void Print() const override
    {
        cout << "Polyline" << endl;

        for (size_t i = 0; i < points.size(); i++)
        {
            cout << "(" << points[i].x << ", " << points[i].y << ")";

            if (i + 1 < points.size())
                cout << " -> ";
        }

        cout << endl;
    }

    void Save(ofstream& file) const override
    {
        file << type << endl;
        file << points.size() << endl;

        for (size_t i = 0; i < points.size(); i++)
        {
            file << points[i].x << " " << points[i].y << endl;
        }
    }

    ~Polyline() override = default;
};

int main()
{
    vector<Shape*> shapes;

    shapes.push_back(new Line({ 1, 2 }, { 10, 5 }));

    shapes.push_back(new Rectangle({ 2, 3 }, 10, 5));

    vector<Point> points;
    points.push_back({ 1, 1 });
    points.push_back({ 5, 3 });
    points.push_back({ 8, 6 });
    points.push_back({ 12, 4 });

    shapes.push_back(new Polyline(points));

    for (size_t i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Print();
        cout << endl;
    }

    ofstream file("shapes.txt");

    if (file.is_open())
    {
        for (size_t i = 0; i < shapes.size(); i++)
        {
            shapes[i]->Save(file);
            file << endl;
        }

        file.close();
        cout << "Figures saved successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }

    for (size_t i = 0; i < shapes.size(); i++)
    {
        delete shapes[i];
    }

    shapes.clear();

    return 0;
}


