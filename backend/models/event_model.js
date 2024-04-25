
const db=require('../database');



const event={
getEvents(id, callback){
        return db.query("CALL showEvents(?)", [id],callback);
    }}

    
module.exports=event;