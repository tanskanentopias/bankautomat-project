const request = require('supertest');
const express = require('express');
const app = express();
const router = require('../routes/student'); 

// Mockataan student_model moduuli
jest.mock('../models/student_model', () => ({
    getAllStudent: jest.fn(),
    getOneStudent: jest.fn(),
    addStudent: jest.fn(),
    updateStudent: jest.fn(),
    deleteStudent: jest.fn()
}));

const student = require('../models/student_model');
app.use('/student', router);

describe('Student API endpoints', () => {
    afterEach(() => {
        jest.clearAllMocks();
    });

    it('GET /student should return all students', async () => {
        const mockstudent = [{ username: 'user01', fname: 'Jussi', lname:'Virtanen', streetaddress:'Isokatu 4', email:'jussi@oamk.fi', password:'qwerty' }, { username: 'user02', fname: 'Aino', lname:'Joki', streetaddress:'Isokatu 2', email:'aino@oamk.fi', password:'qwerty'  }];
        student.getAllStudent.mockImplementationOnce((callback) => {
            callback(null, mockstudent);
        });

        const response = await request(app).get('/student');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockstudent);
    });

    it('GET /student/:user01 should return one student', async () => {
        const mockStudent = {  username: 'user01', fname: 'Jussi', lname:'Virtanen', streetaddress:'Isokatu 4', email:'jussi@oamk.fi', password:'qwerty'  };
        student.getOneStudent.mockImplementationOnce((user01, callback) => {
            callback(null, [mockStudent]);
        });

        const response = await request(app).get('/student/user01');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockStudent);
    });

    it('POST /student should add a new student', async () => {
        const mockStudent = { username: 'user03', fname: 'Teppo', lname:'Testi', streetaddress:'Isokatu 4', email:'teppo@oamk.fi', password:'qwerty' };
        const mockResult = { affectedRows: 1 };
        student.addStudent.mockImplementationOnce((data, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app)
            .post('/student')
            .send(mockStudent);
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });

    it('PUT /student/:usern should update a student', async () => {
        const mockStudent = { username: 'user01', fname: 'New Jussi', lname:'New Virtanen', streetaddress:'Isokatu 4', email:'jussi@oamk.fi', password:'qwerty'  };
        const mockResult = { affectedRows: 1 };
        student.updateStudent.mockImplementationOnce((usern, data, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app)
            .put('/student/user01')
            .send(mockStudent);

        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });

    it('DELETE /student/:usern should delete a student', async () => {
        const mockResult = { affectedRows: 2 };
        student.deleteStudent.mockImplementationOnce((usern, callback) => {
            callback(null, mockResult);
        });

        const response = await request(app).delete('/student/user01');
        expect(response.statusCode).toBe(200);
        expect(response.body).toEqual(mockResult.affectedRows);
    });
});
