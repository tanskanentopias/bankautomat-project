const request = require('supertest');
const express = require('express');
const app = express();
const router = require('../routes/course'); 

// Mockataan course_model moduuli
jest.mock('../models/course_model', () => ({
    getAllCourses: jest.fn(),
    getOneCourse: jest.fn(),
    addCourse: jest.fn(),
    updateCourse: jest.fn(),
    deleteCourse: jest.fn()
}));

const course = require('../models/course_model');
app.use('/course', router);

describe('Course API endpoints', () => {
    afterEach(() => {
        jest.clearAllMocks();
    });

    it('GET /course should return all courses', async () => {
        const mockCourses = [{ idcouse: 1, course_name: 'Java', gredit_points:4 }, { idcouse: 2, course_name: 'C++', gredit_points:5  }];
        course.getAllCourses.mockImplementationOnce((callback) => {
            callback(null, mockCourses);
        });

        const response = await request(app).get('/course');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockCourses);
    });

    it('GET /course/:id should return one course', async () => {
        const mockCourse = { idcouse: 1, course_name: 'Java', gredit_points:4 };
        course.getOneCourse.mockImplementationOnce((id, callback) => {
            callback(null, [mockCourse]);
        });

        const response = await request(app).get('/course/1');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockCourse);
    });

    it('POST /course should add a new course', async () => {
        const mockCourse = { course_name: 'New Course', gredit_points:4 };
        const mockResult = { affectedRows: 1 };
        course.addCourse.mockImplementationOnce((data, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app)
            .post('/course')
            .send(mockCourse);
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });

    it('PUT /course/:id should update a course', async () => {
        const mockCourse = { name: 'Updated Course', gredit_points:3 };
        const mockResult = { affectedRows: 1 };
        course.updateCourse.mockImplementationOnce((id, data, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app)
            .put('/course/1')
            .send(mockCourse);
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });

    it('DELETE /course/:id should delete a course', async () => {
        const mockResult = { affectedRows: 1 };
        course.deleteCourse.mockImplementationOnce((id, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app).delete('/course/1');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });
});
