const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getAccountInfo(callback){
        return db.query("SELECT * FROM account",callback);
    },
    addAccount(newAccount, callback){
            return db.query("INSERT INTO account VALUES(?,?,?,?,?)",[newAccount.id_account, newAccount.balance, newAccount.credit_limit, newAccount.id_user, newAccount.credit_balance],callback);

    },
}

module.exports=card;