const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getCardInfo(callback){
        return db.query("SELECT * FROM card",callback);
    },
    addCard(newCard, callback){
        bcrypt.hash(newCard.password,10,function(err,hashedPassword){
            return db.query("INSERT INTO card VALUES(?,?,?,?)",[newCard.card_serial, newCard.card_type, hashedPassword, newCard.id_account],callback);
        });

    },
    updateCard(cs,updateData, callback){
        bcrypt.hash(updateData.password, 10,function(err,hashedPassword){
            return db.query("UPDATE card SET card_serial=?, card_type=?, card_pin=?, id_account=? WHERE card_serial=?",[updateData.card_serial, updateData.card_type, hashedPassword, updateData.id_account, cs],callback);
        });

    },
    getOneStudent(un, callback){
        return db.query("SELECT * FROM student WHERE username=?",[un],callback);

    },
    deleteCard(id, callback){
        return db.query("DELETE FROM card WHERE id_account=?",[id],callback);
    },
    login(un, callback){
        return db.query("SELECT password FROM student WHERE username=?",[un], callback);
    },
    studentgrade(un, callback){
        return db.query("select course_name, gredit_points,grade, DATE_FORMAT(grade_date,'%d.%m.%Y') as grade_date        from student inner join grade on student.username=grade.username  inner join course on grade.idcourse=course.idcourse WHERE student.username=?",[un],callback);
    }
}

module.exports=card;