from telegram import Update
from telegram.ext import ApplicationBuilder, ContextTypes, CommandHandler


async def start(update=Update, context=ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(chat_id=update.effective_chat.id,
                                   text="/start - post this message \n/create_note - send a message after a"
                                        " certain amount of seconds, format:"
                                        " \"/create_note [time(in seconds)] [message]\"")


async def post_note(context=ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(chat_id=context.job.chat_id, text=context.job.data)


async def create_note(update=Update, context=ContextTypes.DEFAULT_TYPE):
    message = update.message.text.split()
    try:
        time = int(message[1])
    except (IndexError, ValueError):
        await context.bot.send_message(chat_id=update.effective_chat.id,
                                       text='your message should include time (in seconds) after the command')
        return 0

    data = ''
    if len(message) > 2:
        for word in range(2, len(message)):
            data += message[word] + ' '
    else:
        await context.bot.send_message(chat_id=update.effective_chat.id,
                                       text='your note can\'t be empty, please include a note message after the time')
        return 0
    chat_id = update.effective_chat.id
    context.job_queue.run_once(post_note, time, data=data, chat_id=chat_id)

if __name__ == '__main__':
    application = ApplicationBuilder().token('5551706187:AAHuYL6JdlmmSom5JEz4YwVu8EI0ZQo31MQ').build()

    job_queue = application.job_queue

    start_handler = CommandHandler('start', start)
    create_note_handler = CommandHandler('create_note', create_note)

    application.add_handler(start_handler)
    application.add_handler(create_note_handler)

    application.run_polling()
