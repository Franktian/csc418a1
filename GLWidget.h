/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the OpenGL portion of the main window.
**************************************************************************/

#ifndef __GLWidget_h__
#define __GLWidget_h__

#include "include_gl.h"
#include "GLState.h"
#include "GLShape.h"
#include <QtOpenGL/QtOpenGL>

// Penguin Beak
class PenguinBeak : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  -0.5, 0.5 },
            { -0.5,  0.5 },  // Triangle 2
            {  0.5, -0.5 },
            {  0.5,  1   },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Penguin Head
// The basic principles are similar with the unit square, except this
// time we need to one two extra triangle
class PenguinHead : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            { 0.45,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            { 0.45,  0.5 },
            {-0.45,  0.5 },
            {-0.45,  0.5 },  // Triangle 3
            { 0.45,  0.5 },
            {    0,  0.7 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/9,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Penguin Body
// The basic principles are similar with the unit square, except this
// time we need to add two extra triangles
class PenguinBody : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
            { -0.8, -0.2 },  // Triangle 3
            { -0.5, -0.5 },
            { -0.5,  0.5 },
            {  0.5,  0.5 },  // Triangle 4
            {  0.5, -0.5 },
            {  0.8, -0.2 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/12,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};


// Penguin Arm
// This class represents the arm of the penguin
// Note the difference between this shape and unit square is that
// the bottom edge is half the width of top edge
class PenguinArm : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.25, -0.5 },  // Triangle 1
            {  0.25, -0.5 },
            {  0.5,  0.5 },
            { -0.25, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Before transformed, this class displays a unit square centered at the
// origin.
class UnitSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Before transformed, this class displays a unit circle centered at the
// origin.
class UnitCircle : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location, int num_circle_segments)
    {
        // We will draw a circle as a triangle fan.  We are careful to send
	// the second coordinate twice to properly close the circle.
        //        3     2     1
        //         +----+----+
        //        / \   |   /
        //       /   \  |  /
        //      /     \ | /
        //     /       \|/
        //   4+---------+ 0
        //        ...
        std::vector<GLfloat> circle_vertices;
        circle_vertices.push_back(0.0);
        circle_vertices.push_back(0.0);
        for (int i=0; i<=num_circle_segments; ++i)
        {
            double angle = (2 * M_PI * i) / num_circle_segments;
            circle_vertices.push_back(cos(angle));
            circle_vertices.push_back(sin(angle));
        }

        initialize(
	    shader_input_location,
            &circle_vertices[0],
            num_circle_segments + 2,
	    GL_TRIANGLE_FAN);
    }
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // These values control the bounds to display on the joint angle sliders.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Add different ranges for the different joints.  Use these ranges
    //   when constructing sliders and when animating joints.
    //////////////////////////////////////////////////////////////////////////
    static const int JOINT_MIN = -45;
    static const int JOINT_MAX = 45;
    
    // Other ranges
    static const int ARM_MIN = -90;
    static const int ARM_MAX = 90;
    
    static const int BEAK_MIN = 0;
    static const int BEAK_MAX = 5;
    
    static const int HORIZONTAL_MIN = -10;
    static const int HORIZONTAL_MAX = 10;
    
    static const int VERTICAL_MIN = -20;
    static const int VERTICAL_MAX = 20;

    GLWidget(QWidget *parent=NULL);

public slots:
    // This method is called when the user changes the joint angle slider.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   There is currently only one joint, but you need to add more.
    //////////////////////////////////////////////////////////////////////////
    void setJointAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        m_joint_angle = angle;

        // Call update() to trigger a redraw.
        update();
    }
    
    void setArmJointAngle(int angle)
    {
		arm_joint_angle = angle;
		update();
	}
	
	void setBeakJointDistance(int distance)
	{
		beak_joint_distance = distance;
		update();
	}
	
	void setLeftLegJointAngle(int angle)
	{
		left_leg_angle = angle;
		update();
	}
	
	void setLeftLowerLegJointAngle(int angle)
	{
		left_lower_angle = angle;
		update();
	}
	
	void setRightLegJointAngle(int angle)
	{
		right_leg_angle = angle;
		update();
	}
	
	void setRightLowerLegJointAngle(int angle)
	{
		right_lower_angle = angle;
		update();
	}
	
	void setHeadJointAngle(int angle)
	{
		head_joint_angle = angle;
		update();
	}
	
	void setHorizontalDistance(int distance)
	{
		horizontal_distance = distance;
		update();
	}
	
	void setVerticalDistance(int distance)
	{
		vertical_distance = distance;
		update();
	}

    void onPressAnimate(int is_animating)
    {
        // This method is called when the user changes the animation checkbox.
        m_is_animating = (bool)is_animating;
        m_animation_frame = 0;
        update();
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void timerEvent(QTimerEvent *event);

private:
    GLTransformStack &transformStack()
    { return m_gl_state.transformStack(); }

private:
    GLState m_gl_state;
    bool m_is_animating;
    int m_animation_frame;
    UnitSquare m_unit_square;
    UnitCircle m_unit_circle;

    // Self defined shape parameters
    PenguinArm penguin_arm;
    PenguinBody penguin_body;
    PenguinHead penguin_head;
    PenguinBeak penguin_beak;
    //////////////////////////////////////////////////////////////////////////
    // TODO: Add additional joint parameters.
    //////////////////////////////////////////////////////////////////////////
    double m_joint_angle;
    double arm_joint_angle;
    double beak_joint_distance;
    double left_leg_angle;
    double left_lower_angle;
    double right_leg_angle;
    double right_lower_angle;
    double head_joint_angle;
    double horizontal_distance;
    double vertical_distance;
};

#endif
