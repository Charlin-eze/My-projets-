from flask import Flask, render_template, request, url_for,flash
from flask.wrappers import Request
from flask_mysqldb import MySQL
from werkzeug.utils import redirect

app= Flask(__name__)

# Mysql Conecction 
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'flaskcontact'
mysql = MySQL(app)

#Settings
app.secret_key = 'mysecretkey'

@app.route('/')
def Index():
    cur = mysql.connection.cursor()
    cur.execute('SELECT * FROM contacts')
    data = cur.fetchall()
    return render_template('index.html', contacts = data)

@app.route('/add_contact', methods=['POST'])        
def add_contact():
    if request.method == 'POST':
       fullname = request.form['fullname']
       phone = request.form['phone']
       email = request.form['email']
       if fullname :
          cur = mysql.connection.cursor()
          cur.execute('INSERT INTO contacts (fullname, phone, email) VALUES(%s, %s, %s)'
          ,(fullname, phone, email))
          mysql.connection.commit()
          flash('Contact Added successfully')
          return redirect(url_for('Index'))
       else: 
           flash('Not data ingresed')
           return redirect(url_for('Index'))

@app.route('/edit/<id>')
def get_contact(id):
    cur = mysql.connection.cursor()
    cur.execute('SELECT * FROM contacts WHERE id= {0}'.format(id))
    data = cur.fetchall()
    print(data[0])
    return render_template('edit-contact.html', contact = data[0])


@app.route('/update/<id>', methods=['POST'])
def update_contact(id):
    if request.method == 'POST':
     fullname = request.form['fullname']
     phone = request.form['phone']
     email = request.form['email']
     cur = mysql.connection.cursor()
     cur.execute("""
      UPDATE contacts
      SET fullname = %s,
          email = %s,
          phone = %s 
       WHERE id = %s
       """, (fullname, phone, email, id))
     mysql.connection.commit()
     flash('Cotact Update Successfully')
     return redirect(url_for('Index'))



@app.route('/delete/<string:id>')
def delete_contact(id):
    cur = mysql.connection.cursor()
    cur.execute ('DELETE FROM contacts WHERE id= {0}'. format(id))
    mysql.connection.commit()
    flash('Contact Removed Succesfully')
    return redirect(url_for('Index'))

if __name__== '__main__':
   app.run(port = 300, debug=True)

