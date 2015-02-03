/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1
  
  
    Instructions:
        See main.cpp for more instructions.

        This file contains the class for the main window of the program.
**************************************************************************/

#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QtGui/QtGui>
#include "GLWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow()
    {
        // Create a GLWidget to hold the OpenGL viewport.
        m_gl_widget = new GLWidget();

        // Create a checkbox to turn animation on and off, and make it
        // call GLWidget::onPressAnimate when checked.
        m_animate_checkbox = new QCheckBox("Animate", this);
        connect(
            m_animate_checkbox, SIGNAL(stateChanged(int)),
            m_gl_widget, SLOT(onPressAnimate(int)));

        // Create a button to quit the program.
        m_quit_button = new QPushButton("Quit", this);
        connect(
            m_quit_button, SIGNAL(clicked(bool)),
            this, SLOT(onPressQuit(bool)));

        m_main_layout = new QVBoxLayout();
        m_main_layout->addWidget(m_gl_widget);

        //////////////////////////////////////////////////////
        // TODO: Add additional joint sliders here
        //////////////////////////////////////////////////////
        
        // Create arm joint slider
        arm_slider = create_joint_angle_slider(
		"ArmJoint", GLWidget::ARM_MIN, GLWidget::ARM_MAX);
		connect(
            arm_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setArmJointAngle(int)));
            
        // Create beak joint slider
        beak_slider = create_joint_angle_slider(
        "BeakJoint", GLWidget::BEAK_MIN, GLWidget::BEAK_MAX);
        connect(
            beak_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setBeakJointDistance(int)));
            
        // Create leg joint sliders
        left_leg_slider = create_joint_angle_slider(
        "LeftLegJoint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            left_leg_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setLeftLegJointAngle(int)));
            
        left_lower_slider = create_joint_angle_slider(
        "LeftLowerJoint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            left_lower_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setLeftLowerLegJointAngle(int)));
            
        right_leg_slider = create_joint_angle_slider(
        "RightLegJoint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            right_leg_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setRightLegJointAngle(int)));
        
        right_lower_slider = create_joint_angle_slider(
        "RightLowerJoint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            right_lower_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setRightLowerLegJointAngle(int)));
        
        // Create head joint slider
        head_slider = create_joint_angle_slider(
        "HeadJoint", GLWidget::JOINT_MIN, GLWidget::JOINT_MAX);
        connect(
            head_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setHeadJointAngle(int)));

        m_main_layout->addWidget(m_animate_checkbox);
        m_main_layout->addWidget(m_quit_button);
        setLayout(m_main_layout);

        arm_slider->setValue(0);
        beak_slider->setValue(0);
        left_leg_slider->setValue(0);
        left_lower_slider->setValue(0);
        right_leg_slider->setValue(0);
        right_lower_slider->setValue(0);
        head_slider->setValue(0);
        setWindowTitle("CSC418/2504 Assignment 1");
    }

public slots:
    void onPressQuit(bool)
    {
        exit(0);
    }

private:
    QSlider *create_joint_angle_slider(
	const char *label, int min_angle, int max_angle)
    {
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(min_angle, max_angle);
        slider->setSingleStep(1);
        slider->setPageStep(5);
        slider->setTickInterval(5);
        slider->setTickPosition(QSlider::TicksBelow);

	QBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(new QLabel(label));
	layout->addWidget(slider);
	m_main_layout->addLayout(layout);

        return slider;
    }

    GLWidget *m_gl_widget;
    QCheckBox *m_animate_checkbox;
    QPushButton *m_quit_button;
    QVBoxLayout *m_main_layout;

    // New parameter definitions
    QSlider *arm_slider;
    QSlider *beak_slider;
    QSlider *left_leg_slider;
    QSlider *left_lower_slider;
    QSlider *right_leg_slider;
    QSlider *right_lower_slider;
    QSlider *head_slider;
};

#endif
