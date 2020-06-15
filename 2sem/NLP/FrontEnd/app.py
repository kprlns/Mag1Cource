import wtforms
from flask import Flask
from flask import render_template, flash, redirect, request
import form_class

app = Flask(__name__)

text= '<ol><li><p><h2>aaaa</h2></p><p>bbb</p></li></ol>'
text1 = '<div style="word-wrap: break-word; max-width: 800px">\
      sadasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasasassaddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddsaddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddsad\
    </div>'

@app.route('/index', methods=['GET', 'POST'])
@app.route('/', methods=['GET', 'POST'])
def hello_world():
    form = form_class.SearchForm()
    if request.method == 'GET':
        return render_template('index.html', form=form)
    else:
        form1 = form_class.SearchForm(request.form)
        print(form1.search_query.data)
        print(form1.num_of_result.data)
        print(form1.only_headers.data)

        return render_template('index.html', form=form1, text=text1)



if __name__ == '__main__':
    app.run()
