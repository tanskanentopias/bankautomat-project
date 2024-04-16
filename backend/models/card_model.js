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
    getOneCard(cs, callback){
        return db.query("SELECT * FROM card WHERE card_serial=?",[cs],callback);

    },
    deleteCard(cs, callback){
        return db.query("DELETE FROM card WHERE card_serial=?",[cs],callback);
    },
    login(cs, callback){
        return db.query("SELECT card_pin FROM card WHERE card_serial=?",[cs], callback);
    }}

module.exports=card;