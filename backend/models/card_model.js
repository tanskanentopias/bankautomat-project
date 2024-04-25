const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getCardInfo(callback){
        return db.query("SELECT card_serial, card_pin, card_type, card_has_account.account FROM card INNER JOIN card_has_account ON card_has_account.card=card.card_serial",callback);
    },
    addCard(newCard, callback){
        bcrypt.hash(newCard.password,10,function(err,hashedPassword){
            return db.query("INSERT INTO card VALUES(?,?,?,?)",[newCard.card_serial, newCard.card_type, hashedPassword, newCard.id_account],callback);
        });

    },
    updateCard(cs,updateData, callback){
        bcrypt.hash(updateData.card_pin, 10,function(err,hashedPassword){
            return db.query("UPDATE card SET card_serial=?, card_type=?, card_pin=? WHERE card_serial=?",[updateData.card_serial, updateData.card_type, hashedPassword, cs],callback);
        });

    },
    getOneCard(cs, callback){
        return db.query("SELECT * FROM card WHERE card_serial=?",[cs],callback);

    },
    deleteCard(cs, callback){
        return db.query("DELETE FROM card WHERE card_serial=?",[cs],callback);
    },
    /*login(cs, callback){
        return db.query("SELECT card_pin from card WHERE card_serial=?",[cs], callback);
    }}*/
    login(cs, callback){
        return db.query("SELECT card_serial, card_pin, card_type, card_has_account.account FROM card INNER JOIN card_has_account ON card_has_account.card = card.card_serial WHERE card_serial=?",[cs], callback);
    }}

module.exports=card;